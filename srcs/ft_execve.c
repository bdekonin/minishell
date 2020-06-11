/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execve.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 14:50:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/11 17:18:30 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
		length = ft_strlen(head->name) + 1 + ft_strlen(head->content);
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

int					ft_execve(t_vars *v, char *path, char **params)
{
	char **envp;
	int stat;
	pid_t spoon;

	envp = __linkedlist_to_array(v, envp, v->env_head);
	// if (!envp)
	spoon = fork();
	if (!spoon)
	{
		if (execve(path, &params[0], envp) < 0)
		{
			ft_printf("Error - %d\n", errno);
			ft_free_array((void*)envp, env__ft_lstsize(v->env_head));
			exit(EXIT_FAILURE);
		}
	}
	wait(&stat);
	ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
	if (WEXITSTATUS(stat) == EXIT_FAILURE)
		return (0);
	return (1);
}