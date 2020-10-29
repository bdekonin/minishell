/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_relative_path.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/11 19:08:00 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/10/29 16:48:08 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*malloc_relative(t_vars *v, size_t size, char *currentpath, \
														char *command)
{
	char *ptr;

	ptr = ft_calloc(size, sizeof(char));
	if (!ptr)
		ft_exit_error(v, EXIT_FAILURE);
	ft_strlcat(ptr, currentpath, size + 1);
	ft_strlcat(ptr, "/", size + 1);
	ft_strlcat(ptr, (command + 2), size + 1);
	return (ptr);
}

int		get_relative_path(t_vars *v, char **newpath, char **params)
{
	char	*path;
	size_t	count;
	int		ret;

	count = ft_strlen(v->current_path) + 1;
	count += ft_strlen(params[0]) + 1;
	path = malloc_relative(v, count, v->current_path, params[0]);
	if (!path)
		return (FILEERROR);
	*newpath = path;
	return (FILEFOUND);
}