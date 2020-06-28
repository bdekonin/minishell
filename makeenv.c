/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   makeenv.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 13:48:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/28 23:20:08 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int env__makelist(t_vars *v, char **envp)
{
	t_env	*env;
	char	**arr;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i])
	{
		size_t sezeee;
		// system("leaks minishell");
		arr = ft_split(envp[i], '=');
		// // if (!arr)
		// // 	return () error
		// system("leaks minishell");
		if (i == 0)
		{
			v->env_head = env__ft_lstnew(arr[0], arr[1]);
			env = v->env_head;
		}
		else
			env = env__ft_lstnew(arr[0], arr[1]);
		// // if (!env)
		// // 	return () error
		if (!ft_strcmp("LOGNAME", arr[0]))
			v->__logname = env;
		else if (!ft_strcmp("HOME", arr[0]))
			v->__homedir = env;
		else if (!ft_strcmp("OLDPWD", arr[0]))
		{
			temp = ft_calloc(PATH_MAX ,sizeof(char));
			// // if (!temp)
			// // 	return () error
			ft_strlcpy(temp, env->content, ft_strlen(env->content));
			free(env->content);
			env->content = temp;
			v->__oldpwd = env;
		}
		// else if (!ft_strcmp("OLDPWD", arr[0]))
		if (i != 0)
			env__ft_lstadd_back(&v->env_head, env);
		free(arr[2]);
		free(arr);
		i++;
	}
	// !LOGNAME
	// !HOME
	// !OLDPWD
	env = env__ft_lstlast(v->env_head);
	v->__executable = ft_strrchr(env->content, '.');
	return (1);
}