/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_static_more.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 14:37:13 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/04 14:44:43 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_searchdir(struct dirent **dp, char *command, DIR *dir)
{
	if (!ft_strncmp(dp[0]->d_name, command, ft_strlen(dp[0]->d_name)))
	{
		if (closedir(dir) < 0)
			return (FILEERROR);
		return (FILEFOUND);
	}
	dp[0] = readdir(dir);
	if (dp[0] < 0)
	{
		closedir(dir);
		return (FILEERROR);
	}
	return (0);
}

int	searchdir(char *location, char *command)
{
	struct dirent	*dp;
	DIR				*dir;
	int				ret;

	dir = opendir(location);
	if (!dir)
		return (2);
	dp = readdir(dir);
	if (dp < 0)
	{
		closedir(dir);
		return (FILEERROR);
	}
	while (dp)
	{
		ret = loop_searchdir(&dp, command, dir);
		if (ret == FILEFOUND)
			return (ret);
	}
	if (closedir(dir) < 0)
		return (FILEERROR);
	return (FILENOTFOUND);
}
