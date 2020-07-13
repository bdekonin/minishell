/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_relativepath.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/11 19:08:00 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/11 21:34:36 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"
#include <sys/stat.h>

static inline char	*malloc_relative(size_t size, char *currentpath, \
														char *command)
{
	char *ptr;

	ptr = ft_calloc(size, sizeof(char));
	if (!ptr)
		return (NULL);
	ptr = ft_strcat(ptr, currentpath);
	ptr = ft_strcat(ptr, "/");
	ptr = ft_strcat(ptr, (command + 2));
	return (ptr);
}

static inline int	validate_file(char *filepath)
{
	struct stat	sb;
	int			ret;

	ret = stat(filepath, &sb);
	if (ret == 0)
	{
		if (sb.st_mode & S_IXUSR)
			return (1);
		else
			return (0);
	}
	else
		return (-1);
}

int					get_relativepath(char *currentpath, \
								char **newpath, char *command)
{
	char		*path;
	size_t		count;
	int			ret;

	count = ft_strlen(currentpath) + 1;
	count += ft_strlen(command) + 1;
	path = malloc_relative(count, currentpath, command);
	if (!path)
		return (-1);
	ret = validate_file(path);
	if (ret == 1)
	{
		*newpath = path;
		return (1);
	}
	else
	{
		free(path);
		return (ret);
	}
}
