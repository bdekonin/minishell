/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 22:54:51 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/09/14 17:30:17 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline int	cd_arguments(t_vars *v, char **argument, char *oldpwd_backup)
{
	char		*tmp;
	int			ret;

	ft_strlcpy(oldpwd_backup, v->current_path, ft_strlen(v->current_path) + 1);
	if (!argument[0] || !ft_strncmp(argument[0], "--", 3) || !ft_strncmp(argument[0], "~", 2))
		ret = chdir(v->default_homedir->content);
	else if (!ft_strncmp(argument[0], "-", 3))
	{
		ft_printf("%s\n", v->default_oldpwd->content);
		ret = chdir(v->default_oldpwd->content);
	}
	else
	{
		ret = chdir(argument[0]);
		if (ret < 0)
			ft_printf("%s: cd: %s: %s\n", v->default_executable->content, argument[0], strerror(errno));
	}
	return (ret);
}

int					ft_cd(t_vars *v, char **params)
{
	int			ret_chdir;
	char		oldpwd_backup[PATH_MAX];

	//check for multiple arguments = error (see bash)
	ret_chdir = cd_arguments(v, params, oldpwd_backup);
	if (ret_chdir == -1 && ft_iserrno(ENOMEM))
		return (0);
	// if (ret_chdir == -1)
	// {
	// 	if (!sethistory(&v->history_head, v->line, "1"))
	// 		return (0);
	// }
	// else
	// {
	// 	if (!sethistory(&v->history_head, v->line, "0"))
	// 		return (0);
	// 	ft_strlcpy(v->default_oldpwd->content, oldpwd_backup, PATH_MAX);
	// }
	v->current_path = getcwd(v->current_path, PATH_MAX);
	if (!v->current_path)
		return (0);
	return (1);
}