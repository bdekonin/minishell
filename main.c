/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 10:35:22 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 10:13:31 by bdekonin      ########   odam.nl         */
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

int segfault = 0;

int env__makelist(t_vars *v, char **envp)
{
	t_env	*env;
	char	*name;
	char	*content;
	int		loc;
	int		i;

	i = 1;
	loc = ft_charsearch(envp[0], '='); // make better function; universal one
	name = ft_substr(envp[0], 0, loc);
	content = ft_substr(envp[0], loc + 1, ft_strlen(envp[0] + loc));
	if (!name || !content)
		return (0);
	env = env__ft_lstnew(name, content);
	while (envp[i])
	{
		loc = ft_charsearch(envp[i], '='); // make better function; universal one
		name = ft_substr(envp[i], 0, loc);
		content = ft_substr(envp[i], loc + 1, ft_strlen(envp[i] + loc));
		if (!name || !content)
			return (0);
		env__ft_lstadd_back(&env, env__ft_lstnew(name, content));
		i++;
	}
	v->env_head = env;
	while (env)
	{
		if (!ft_strncmp("LOGNAME", env->name, ft_strlen(env->name)))
			v->__logname = env->content;
		if (!ft_strncmp("HOME", env->name, ft_strlen(env->name)))
			v->__homedir = env->content;
		if (!ft_strncmp("PWD", env->name, ft_strlen(env->name)))
		{
			free(env->content);
			env->content = v->current_path;
		}
		if (!ft_strncmp("OLDPWD", env->name, ft_strlen(env->name))) // will go in here if you run it seperate
		{
			v->__oldpwd = ft_calloc(PATH_MAX, sizeof(char));
			if (!v->__oldpwd)
				return (0);
			v->__oldpwd = ft_memcpy(v->__oldpwd, env->content, ft_strlen(env->content));
			free(env->content);
			env->content = v->__oldpwd;
		}
		env = env->next;
	}
	if (!v->__ppid)
	{
		v->__ppid = ft_itoa(getpid());
		if (!v->__ppid)
			return (0);
		env__ft_lstadd_front(&v->env_head, env__ft_lstnew(ft_strdup("PPID"), v->__ppid));
	}
	if (!v->__oldpwd)
	{
		v->__oldpwd = ft_calloc(PATH_MAX, sizeof(char));
		ft_memcpy(v->__oldpwd, v->current_path, ft_strlen(v->current_path));
		env__ft_lstadd_front(&v->env_head, env__ft_lstnew(ft_strdup("OLDPWD"), v->__oldpwd));
	}
	env = env__ft_lstlast(v->env_head);
	v->__executable = ft_strrchr(env->content, '.');
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	ft_printf("---- Starting ----\n\n");
	t_vars v;
	argc++; //  TIJDELIJK VOOR DE WARNING
	argv[0] = NULL; // TIJDELIJK VOOR DE WARNING
	v.__oldpwd = NULL;
	v.__ppid = NULL;

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
	env__makelist(&v, envp);

	/*
	** End initializing prompt
	*/

	int stat;
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		read_user_input(&v);
	}
}
