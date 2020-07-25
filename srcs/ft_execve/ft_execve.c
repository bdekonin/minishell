/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execve.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 14:50:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/25 12:41:39 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** https://tldp.org/LDP/abs/html/exitcodes.html
*/

/*
** Converts the linked list environ to a array of strings. Terminated by NULL.
**
** @param  t_vars v		vars
** @param  char **envp	array which will be filled.
** @param  t_end *head	Pointer to first argument of environ linked list.
**
** @return char **		envp (filled)
*/

static char			**__linkedlist_to_array(t_vars *v, char **envp, t_env *head)
{
	int			i;
	size_t		size;
	size_t		length;

	i = 0;
	size = env__ft_lstsize(v->env_head);
	envp = ft_calloc(size + 1, sizeof(char*));
	if (!envp)
		return (NULL);
	while (head)
	{
		length = ft_strlen(head->name) + 2 + ft_strlen(head->content);
		envp[i] = ft_calloc(length, sizeof(char));
		if (!envp[i])
		{
			ft_free_array((void*)envp, i - 1);
			return (NULL);
		}
		ft_strcat(envp[i], head->name);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], head->content);
		head = head->next;
		i++;
	}
	return (envp);
}

void makething(t_cmd *cmd, char ***params, char *str, size_t *splitsize)
{
	size_t i;
	size_t size;
	char **arr;
	char **argv;

	i = 0;
	arr = ft_split_sep(str, " \t", &size);
	for (int j = 0; arr[j]; j++)
	argv = ft_calloc(100, sizeof(char*)); // LEAK
	while (params[0][i])
	{
		argv[i] = ft_strdup(params[0][i]);
		//protec
		i++;
	}
	int j = 0;
	while (arr[j])
	{
		argv[i] = arr[j];
		i++;
		j++;
	}
	// ft_free_array((void*)arr, size);
	// ft_free_array((void*)params[0], ft_wordcount(cmd->line));
	free(arr);
	ft_free_array((void*)params[0], *splitsize);
	*splitsize = 100; // LEAK
	// for (int j = 0; arr[j]; j++)
	// {
	// 	ft_printf("arr[%d]: %s\n", j, arr[j]);
	// }
	// ft_printf("\n");
	// for (int j = 0; params[0][j]; j++)
	// {
	// 	ft_printf("params[%d]: %s\n", j, params[0][j]);
	// }
	// ft_printf("\n");
	// for (int j = 0; argv[j]; j++)
	// {
	// 	ft_printf("argv[%d]: %s\n", j, argv[j]);
	// }
	params[0] = argv;
}

void check_stdin_arguments(t_cmd *cmd,  char ***params, size_t *splitsize)
{
	size_t wordcount;
	char *str;

	str = NULL;
	if (cmd->next)
	{
		str = cmd->next->line;
		wordcount = ft_wordcount(str);
		if (cmd->type != PIPE && cmd->next && wordcount >= 2)
		{
			str[ft_strlcpy(str, str + (ft_strchr(str, ' ') - str + 1), ft_strlen(str))] = 0;
			makething(cmd, params, str, splitsize); // BETTER NAME
		}
	}

}

/*
** Executes binary/executable based on arguments
**
** @param  t_vars v			vars
** @param  char *path		path of executable e.g. -> "/usr/bin/leaks"
** @param  char **params	parameters of input e.g. ↓ (Has to be NULL terminated)
**													{leaks},
**													{minishell},
**													{NULL}
**
** @return char **			envp (filled)
*/

/*
**	Finished	1 - (....)
**	Not found	0 - (null)
**	Error	   -1 - (null)
*/
int		ft_execve(t_vars *v, t_cmd *cmd, char ***params, size_t *splitsize)
{
	char *path;
	char **envp;
	int ii;
	int stat;
	
	path = NULL;
	ii = find_executable(v, &path, params[0][0]);
	if (ii < 0)
		return (-1); // error
	else if (ii == 0)
		return (0); // no command found
	envp = NULL;
	envp = __linkedlist_to_array(v, envp, v->env_head); // return or parameter not both bitch
	if (!envp)
	{
		free(path);
		return (-1);
	}
	// check_stdin_arguments(cmd, params, splitsize);
	pid_t	spoon = fork();
	if (!spoon)
	{
		signal(SIGINT, SIG_DFL); // ctrl c - for cat so you can quit
		signal(SIGTSTP, SIG_DFL); // ctrl z
		if (execve(path, params[0], envp) < 0)
		{
			ft_printf("%s: %s\n", v->__executable->content, strerror(errno));
			exit(COMMAND_NOT_RUNNABLE);
		}
	}
	else
		wait(&stat);
	ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
	free(path);
	// path = ft_itoa(WEXITSTATUS(stat));
	if (!sethistory(&v->history_head, v->line, "EXECVE"))
	{
		// free(path)
		return (0);
	}
	// free(path);
	return (1);
	(void)(cmd);

}
