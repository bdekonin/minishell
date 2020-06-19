/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 22:54:51 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/18 11:57:42 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"


int cd(t_vars *v, t_node *node, char **params, char **ret)
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
	** invalid
	** cd ; cd Documents/Project/minishell // error
	** cd ; pwd ; cd $q/$k	//this will not work
	**
	** valid
	** cd $HOME/Documents
	** pwd ; cd $HOME ; pwd
	** cd minishell/$s
	** cd ; pwd ; cd Documents/Projects/$p/$s
	** cd ; pwd ; cd $p/$s/utils
	** cd ; pwd ; cd Documents/Projects/$p
	** cd Project\$p
	** cd Test\ ing\ ing/
	** cd Test\ ing\ ing
	** cd ; pwd ; cd Documents/Projects/$p/Test\ ing\ ing/
	*/
	char		*dir;
	int			ret_chdir;
	char 		oldpwd_backup[PATH_MAX];

	ft_strlcpy(oldpwd_backup, v->current_path, ft_strlen(v->current_path) + 1);
	if (!params[0] || !ft_strncmp("|", params[0], 3))
		ret_chdir = chdir(v->__homedir->content);
	else if (!ft_strncmp(params[0], "--", 3) || !ft_strncmp(params[0], "~", 2))
		ret_chdir = chdir(v->__homedir->content);
	else if (!ft_strncmp(params[0], "-", 3))
	{
		ft_printf("%s\n", v->__oldpwd);
		ret_chdir = chdir(v->__oldpwd);
	}
	else
	{
		dir = removespace(v, ft_strnstr(node->line, "cd", ft_strlen(node->line)) + 2);
		if (!dir)
			return (0);
		ret_chdir = chdir(dir);
		if (ret_chdir == -1)
			ft_printf("cd: no such file or directory: %s\n", dir);
		free(dir);
	}
	if (ret_chdir == -1)
		*ret = ft_strdup("1");
	else
	{
		*ret = ft_strdup("0");
		ft_strlcpy(v->__oldpwd, oldpwd_backup, PATH_MAX);
	}
	v->current_path = getcwd(v->current_path, PATH_MAX);
	return (1);
}