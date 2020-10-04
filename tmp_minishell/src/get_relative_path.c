/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_relative_path.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/11 19:08:00 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/09/14 17:40:18 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*malloc_relative(size_t size, char *currentpath, \
														char *command)
{
	char *ptr;

	ptr = ft_calloc(size, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcat(ptr, currentpath, size + 1);
	ft_strlcat(ptr, "/", size + 1);
	ft_strlcat(ptr, (command + 2), size + 1);
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

int		get_relative_path(t_vars *v, char **new_path, char **tokens)
{
	char	*path;
	size_t	count;
	int		ret;

	count = ft_strlen(v->current_path) + 1;
	count += ft_strlen(tokens[0]) + 1;
	path = malloc_relative(count, v->current_path, tokens[0]);
	if (!path)
		return (-1);
	ret = validate_file(path);
	if (ret == 1)
	{
		*new_path = path;
		return (1);
	}
	else
	{
		free(path);
		return (ret);
	}
}