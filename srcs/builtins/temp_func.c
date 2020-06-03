/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/03 20:55:07 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** Sources
** https://www.computerhope.com/unix/ucd.htm
**
** $HOME =	[/Users/bdekonin]
** $p = 	[minishell]
** $s = 	[srcs]
** $k =		N/A
** $q =		N/A
**
** cd $HOME/Documents
** pwd ; cd $HOME ; pwd
** cd minishell/$s
** cd ; pwd ; cd $q/$k	ERROR
** cd ; pwd ; cd Documents/Projects/$p/$s
** cd ; pwd ; cd $p/$s/utils
** cd ; pwd ; cd Documents/Projects/$p
** cd Project\$p
** cd Test\ ing\ ing/
** cd Test\ ing\ ing
** cd ; pwd ; cd Documents/Projects/$p/Test\ ing\ ing/
** cd ; cd Documents/Project/minishell
*/

int cd(t_vars *v, char **params)
{
	char		*dir;
	int			i;
	int			ret;
	char 		oldpwd_backup[PATH_MAX];

	i = 0;
	// dir = NULL;
	ft_strlcpy(oldpwd_backup, v->current_path, ft_strlen(v->current_path) + 1);
	if (!params[i])
		ret = chdir(v->__homedir);
	else if (!ft_strncmp(params[i], "--", 3) || !ft_strncmp(params[i], "~", 2))
		ret = chdir(v->__homedir);
	else if (!ft_strncmp(params[i], "-", 3))
		ret = chdir(v->__oldpwd);
	else
	{
		dir = removespace(v, ft_strnstr(v->argv[v->i], "cd", ft_strlen(v->argv[v->i])) + 2);
		if (!dir)
			return (0);
		ret = chdir(dir);
		if (ret == -1)
			ft_printf("cd: no such file or directory: %s\n", dir);
		free(dir);
	}
	if (ret == -1)
		v->argument_ret = ft_strdup("1");
	else
	{
		v->argument_ret = ft_strdup("0");
		ft_strlcpy(v->__oldpwd, oldpwd_backup, PATH_MAX);
	}
	v->current_path = getcwd(v->current_path, PATH_MAX);
	return (1);
}

int pwd(t_vars *v, char **params)
{
	v->current_path = getcwd(v->current_path, PATH_MAX);
	if (!v->current_path)
		ft_printf("ERROR\n");
	else
		v->argument_ret = ft_strdup(v->current_path);
	ft_printf("%s\n", v->current_path);
	(void)(params);
	return (1);
}

int echo(t_vars *v, char **params)
{
	ft_printf("%.0s\t", v->__executable);
	for (int i = 0; params[i]; i++)
		ft_printf("echo\t%s\n", params[i]);
	v->argument_ret = ft_strdup("1");
	(void)(params);
	return (1);
}

// The return status is zero unless a name does not exist or is readonly.
int unset(t_vars *v, char **params)
{
	env__ft_lstremove_middle(params[0], v->env_head);
	v->argument_ret = ft_strdup("1");
	(void)(params);
	return (1);
}

int env(t_vars *v, char **params)
{
	t_env *env;

	env = v->env_head;
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	v->argument_ret = ft_strdup("1");
	return (1);
}

int exitt(t_vars *v, char **params)
{
	env__ft_lstclear(&v->env_head, free);
	his__ft_lstclear(&v->history_head, free); // DO THIS
	exit(EXIT_SUCCESS);
	return (1);
}
int help(t_vars *v, char **params)
{
	t_history *kaas = v->history_head;
	ft_printf("\n\nline\t\t\tcommand\t\toutput\n");
	ft_printf("[%s]\t[%s]\t[%s]\n", v->line, v->argv[v->i], "???");
	while (kaas)
	{
		ft_printf("[%s]\t[%s]\t[%s]\n", kaas->line, kaas->command, kaas->output);
		kaas = kaas->next;
	}
	v->argument_ret = ft_strdup("1");
	return (1);
}
