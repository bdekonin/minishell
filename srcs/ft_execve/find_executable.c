/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_executable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 15:33:31 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/10 16:03:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int			listfiles(const char *path, const char *command)
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
		if (!ft_strcmp(dp->d_name, command))
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

static char			*make_command(char *path, char *command)
{
	size_t		length;
	char		*newpath;

	length = ft_strlen(path) + 1 + ft_strlen(command) + 1;
	newpath = ft_calloc(length, sizeof(char));
	if (!newpath)
		return (NULL);
	ft_strcat(newpath, path);
	ft_strcat(newpath, "/");
	ft_strcat(newpath, command);
	return (newpath);
}

static inline int	loop_locations(int size, char **argv_dirs, \
						char *command, char **newpath)
{
	int j;
	int ret;

	j = 0;
	while (j < (int)size)
	{
		*newpath = NULL;
		ret = listfiles(argv_dirs[j], command);
		if (ret == 1)
		{
			*newpath = make_command(argv_dirs[j], command);
			if (!*newpath)
				return (-1);
			return (1);
		}
		else if (ret < 0 && !ft_iserrno(ENOENT) && \
						!ft_iserrno(EACCES) && !ft_iserrno(ENOTDIR))
			return (-1);
		j++;
	}
	return (0);
}

int					find_executable(t_vars *v, char **newpath, char *command)
{
	char	**argv_dirs;
	size_t	size;
	int		ret;

	argv_dirs = ft_split_sep(v->__path->content, ":", &size);
	if (!argv_dirs)
		return (-1);
	ret = loop_locations((int)size, argv_dirs, command, newpath);
	ft_free_array((void*)argv_dirs, size);
	if (ret == -1 || ret == 1)
		return (ret);
	return (0);
}
