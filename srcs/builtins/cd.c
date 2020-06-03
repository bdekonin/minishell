/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 22:54:51 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/03 22:55:40 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"


int cd(t_vars *v, char **params)
{
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