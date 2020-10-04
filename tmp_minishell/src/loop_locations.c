/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_locations.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/12 15:29:45 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/14 17:43:10 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*make_command(t_vars *v, const char *path, char **params)
{
	size_t		length;
	char		*newpath;

	length = ft_strlen(path) + 1 + ft_strlen(params[0]) + 1;
	newpath = ft_calloc(length, sizeof(char));
	if (!newpath)
		return (NULL);
	ft_strlcat(newpath, path, length + 1);
	ft_strlcat(newpath, "/", length + 1);
	ft_strlcat(newpath, params[0], length + 1);
	return (newpath);
}

static int			list_files(t_vars *v, const char *path, char **params)
{
	struct dirent *dp;
	DIR *dir = opendir(path); //norm

	if (!dir)
		return (-1);
	dp = readdir(dir);
	if (dp < 0)
	{
		closedir(dir);
		return (-1);
	}
	while (dp)
	{
		if (!ft_strcmp(dp->d_name, params[0]))
		{
			if (closedir(dir) < 0)
				return (-1);
			return (1);
		}
		dp = readdir(dir);
		if (dp < 0)
		{
			closedir(dir);
			return (-1);
		}
	}
	if (closedir(dir) < 0)
		return (-1);
	return (0);
}

int	loop_locations(t_vars *v, char **new_path, char **params)
{
	char	**argv;
	size_t	size;
	size_t	i;
	int		ret;
	
	argv = ft_split_multi(v->default_path->content, ":", &size);
	if (!argv)
		return (-1);
	i = 0;
	while (i < size)
	{
		ret = list_files(v, argv[i], params);
		if (ret == 1)
		{
			*new_path = make_command(v, argv[i], params);
			if (!*new_path)
			{
				ft_free_array((void **)argv, size);
				return (-1);
			}
			return (1);
		}
		else if (ret < 0 && !ft_iserrno(ENOENT) && !ft_iserrno(EACCES) && !ft_iserrno(ENOTDIR))
		{
			ft_free_array((void **)argv, size);
			return (-1);
		}
		i++;
	}
	return (ft_free_array((void **)argv, size));
}
