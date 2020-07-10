/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execve.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 14:50:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/10 16:02:40 by bdekonin      ########   odam.nl         */
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
int					ft_execve(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	char *path;
	char **envp;
	int ii;
	int stat;
	
	path = NULL;
	ii = find_executable(v, &path, params[0]);
	if (ii < 0)
		return (-1);
	else if (ii == 0)
		return (0);
	envp = NULL;
	envp = __linkedlist_to_array(v, envp, v->env_head); // return or parameter not both bitch
	if (!envp)
	{
		free(path);
		return (-1);
	}
	pid_t	spoon = fork();
	if (!spoon)
	{
		signal(SIGINT, SIG_DFL); // ctrl c - for cat so you can quit
		signal(SIGTSTP, SIG_DFL); // ctrl z
		if (execve(path, params, envp) < 0)
		{
			ft_printf("%s: %s\n", v->__executable + 2, strerror(errno));
			exit(COMMAND_NOT_RUNNABLE);
		}
	}
	wait(&stat);
	ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
	free(path);
	*ret = ft_itoa(WEXITSTATUS(stat));
	if (!*ret)
		return (0);
	return (1);
	(void)(cmd);

}
