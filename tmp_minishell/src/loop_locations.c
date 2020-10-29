/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_locations.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/12 15:29:45 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/29 16:41:20 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <sys/stat.h>

static int searchDir(char *location, char *command)
{
	struct dirent *dp;
	DIR *dir;

	dir = opendir(location);
	if (!dir)
		return (FILEERROR);
	dp = readdir(dir);
	if (dp < 0)
	{
		closedir(dir);
		return (FILEERROR);
	}
	while (dp)
	{
		if (!ft_strncmp(dp->d_name, command, ft_strlen(dp->d_name)))
		{
			if (closedir(dir) < 0)
				return (FILEERROR);
			return (FILEFOUND);
		}
		dp = readdir(dir);
		if (dp < 0)
		{
			closedir(dir);
			return (FILEERROR);
		}
	}
	if (closedir(dir) < 0)
		return (FILEERROR);
	return (FILENOTFOUND);
}

int	loop_locations(t_vars *v, char **new_path, char **params)
{
	char **locations;
	size_t splitsize;
	int i;
	int ret;

	i = 0;
	ret = 0;
	locations = ft_split_multi(v->default_path->content, ":", &splitsize);
	if (!locations)
		return (FILEERROR);
	while (locations[i])
	{
		ret = searchDir(locations[i], params[0]);
		if (ret == FILEFOUND)
		{
			*new_path = ft_strdup(locations[i]);
			break;
		}
		if (ret == FILEERROR)
			return (ret);
		i++;
	}
	ft_free_array((void**)locations, splitsize);
	return (ret);
}

int	handleLocations(t_vars *v, char **newpath, char **params)
{
	char *path;
	char *totalpath;

	int ret;
	size_t length;

	ret = loop_locations(v, &path, params);
	if (ret == FILENOTFOUND || ret == FILEERROR)
		return (ret);
	length = ft_strlen(path) + 1 + ft_strlen(params[0]) + 1; // pwd + / + command + \0
	totalpath = ft_calloc(length , sizeof(char));
	if (!totalpath)
		return (FILEERROR); // Malloc		
	ft_strlcat(totalpath, path, length + 1);
	ft_strlcat(totalpath, "/", length + 1);
	ft_strlcat(totalpath, params[0], length + 1);
	*newpath = totalpath;
	return (ret);
}
