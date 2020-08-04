/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 22:54:51 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/08/04 13:25:59 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static inline int	cd_2(t_vars *v, t_cmd *cmd, char *argument, \
														char *oldpwd_backup)
{
	char		*dir;
	int			ret;

	ft_strlcpy(oldpwd_backup, v->current_path, ft_strlen(v->current_path) + 1);
	if (!argument || !ft_strncmp(argument, "--", 3) || \
											!ft_strncmp(argument, "~", 2))
		ret = chdir(v->__homedir->content);
	else if (!ft_strncmp(argument, "-", 3))
	{
		ft_printf("%s\n", v->__oldpwd->content);
		ret = chdir(v->__oldpwd->content);
	}
	else
	{
		dir = parse_cd(v, ft_strnstr(cmd->line, "cd", \
								ft_strlen(cmd->line)) + 2);
		if (!dir)
			return (-1);
		ret = chdir(dir);
		if (ret == -1)
			ft_printf("%s: cd: %s: %s\n", v->__executable->content, \
												dir, strerror(errno));
		free(dir);
	}
	return (ret);
}

int					cd(t_vars *v, t_cmd *cmd, char **params)
{
	int			ret_chdir;
	char		oldpwd_backup[PATH_MAX];

	ret_chdir = cd_2(v, cmd, params[0], oldpwd_backup);
	if (ret_chdir == -1 && ft_iserrno(ENOMEM))
		return (0);
	if (ret_chdir == -1)
	{
		if (!sethistory(&v->history_head, v->line, "1"))
			return (0);
	}
	else
	{
		if (!sethistory(&v->history_head, v->line, "0"))
			return (0);
		ft_strlcpy(v->__oldpwd->content, oldpwd_backup, PATH_MAX);
	}
	v->current_path = getcwd(v->current_path, PATH_MAX);
	if (!v->current_path)
		return (0);
	return (1);
}