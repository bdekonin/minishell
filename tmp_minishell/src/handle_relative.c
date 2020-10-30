/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_relative.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/11 19:08:00 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/10/30 20:18:41 by bdekonin      ########   odam.nl         */
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

static char *get_relative_path(char *currentpath, char *command)
{
	char	*path;
	size_t	count;
	int		ret;

	count = ft_strlen(currentpath) + 1;
	count += ft_strlen(command) + 1;
	path = malloc_relative(count, currentpath, command);
	return (path);
}

int handle_relative(t_vars *v, char **newpath, char *command)
{
	char *path;
	int ret;
	
	path = get_relative_path(v->current_path, command);
	if (!path)
		return (FILEERROR);

	*newpath = path;
	ret = validate_file(path);


	if (ret == FILEFOUND)
		return (FILEFOUND);

	// Errors
	if (ret == FILEPERMISSIONS)
		ft_printerror(command, EACCES); 
	else if (ret == FILENOTFOUND)
		ft_printerror(command, ENOENT); 
	free(*newpath);
	return (ret);
}