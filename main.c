/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 10:35:22 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/02 00:04:48 by bdekonin      ########   odam.nl         */
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
int env__makelist(t_vars *v, char **envp);

// export PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin:/Users/bdekonin/Documents/Projects/minishell

// int env__makelist(t_vars *v, char **envp)
// {
// 	t_env	*env;
// 	char	*tmp;
// 	int		i;
// 	char **arr;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		arr = ft_split(envp[i], '=');
// 		if (!arr)
// 			return (0); // free stuff maybe
// 		// ft_printf("strncmp = %d - %s\n", ft_strncmp("CURRENT_PID", arr[0], 13), arr[0]);
// 		if (i == 0)
// 			env = env__ft_lstnew(arr[0], arr[1]);
// 		else
// 			env__ft_lstadd_back(&env, env__ft_lstnew(arr[0], arr[1]));
// 		i++;
// 	}
// 	v->env_head = env;
// 	while (env)
// 	{
// 		if (!ft_strncmp("LOGNAME", env->name, ft_strlen(env->name)))
// 			v->__logname = env;
// 		if (!ft_strncmp("HOME", env->name, ft_strlen(env->name)))
// 			v->__homedir = env;
// 		if (!ft_strncmp("PWD", env->name, ft_strlen(env->name)))
// 		{
// 			free(env->content);
// 			env->content = v->current_path;
// 		}
// 		if (!ft_strncmp("OLDPWD", env->name, ft_strlen(env->name))) // will go in here if you run it seperate
// 		{
// 			v->__oldpwd = ft_calloc(PATH_MAX, sizeof(char));
// 			if (!v->__oldpwd)
// 				return (0);
// 			v->__oldpwd = ft_memcpy(v->__oldpwd, env->content, ft_strlen(env->content));
// 			free(env->content);
// 			env->content = v->__oldpwd;
// 		}
// 		if (!ft_strncmp("PATH", env->name, ft_strlen(env->name))) // will go in here if you run it seperate
// 		{
// 			v->__path = env;
// 			tmp = ft_calloc(ft_strlen(v->current_path) + 2 + ft_strlen(v->__path->content), sizeof(char));
// 			if (!tmp)
// 				return (0);
// 			ft_strcat(tmp, v->__path->content);
// 			ft_printf("Return = %s\n", v->current_path, env->content);
// 			if (!ft_strnstr(env->content, v->current_path, PATH_MAX))
// 			{
// 				ft_strcat(tmp, ":");
// 				ft_strcat(tmp, v->current_path);
// 			}
// 			free(v->__path->content);
// 			v->__path->content = tmp;
// 		}
// 		if (!ft_strncmp("PARENT_PID", env->name, ft_strlen(env->name))) // will go in here if you run it seperate
// 			v->__parentpid = env->content;
// 		if (!ft_strncmp("CURRENT_PID", env->name, ft_strlen(env->name))) // will go in here if you run it seperate
// 		{
// 			free(env->content);
// 			v->__currentpid = ft_itoa(getpid());
// 			if (!v->__currentpid)
// 				return (0);
// 			env->content = v->__currentpid;
// 		}
// 		env = env->next;
// 	}
// 	if (!v->__parentpid)
// 	{
// 		v->__parentpid = ft_itoa(getpid());
// 		if (!v->__parentpid)
// 			return (0);
// 		env__ft_lstadd_front(&v->env_head, env__ft_lstnew(ft_strdup("PARENT_PID"), v->__parentpid));
// 	}
// 	if (!v->__oldpwd)
// 	{
// 		v->__oldpwd = ft_calloc(PATH_MAX, sizeof(char));
// 		ft_memcpy(v->__oldpwd, v->current_path, ft_strlen(v->current_path));
// 		env__ft_lstadd_front(&v->env_head, env__ft_lstnew(ft_strdup("OLDPWD"), v->__oldpwd));
// 	}
// 	if (!v->__currentpid)
// 	{
// 		v->__currentpid = ft_itoa(getpid());
// 		if (!v->__currentpid)
// 			return (0);
// 		env__ft_lstadd_front(&v->env_head, env__ft_lstnew(ft_strdup("CURRENT_PID"), v->__currentpid));
// 	}
// 	env = env__ft_lstlast(v->env_head);
// 	v->__executable = ft_strrchr(env->content, '.');
// 	return (1);
// }

void	read_user_input(t_vars *v);

int main(int argc, char **argv, char **envp)
{
	ft_printf("---- Starting ----\n\n");
	t_vars v;
	(void)argc; // voor de warnign
	(void)argv; // voor de warnign
	v.__oldpwd = NULL; // can be overwritten. needs to be malloced size of pathmax
	v.__parentpid = NULL; // cant be overwritten.
	v.__currentpid = NULL; // cant be overwritten.

	v.history_head = NULL;

	ft_printf("pid = %d\n", getpid());
	/*
	** Initializing prompt
	*/
	v.prefix = ft_strdup(d_prefix);
	if (!v.prefix)
		return (0);
	v.current_path = ft_calloc(PATH_MAX, sizeof(char));
	if (!v.current_path)
		return (0);
	v.current_path = getcwd(v.current_path, PATH_MAX);

	env__makelist(&v, envp); // leak in here
	// exit(1);
	/*
	** End initializing prompt
	*/
	signal(SIGINT, SIG_IGN); // ctrl c
	signal(SIGTSTP, SIG_IGN); // ctrl z

	while (1)
	{
		read_user_input(&v);
		node__ft_lstclear(&v.nodehead, free);
	}
}

// /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin:/Users/bdekonin/Documents/Projects/minishell