/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_static.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/12 15:29:45 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/04 14:45:30 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**invalid_path(t_vars *v, size_t *splitsize)
{
	char **argv;

	argv = ft_calloc(2, sizeof(char*));
	malloc_check(v, argv);
	argv[0] = ft_strdup(v->current_path);
	malloc_check(v, argv[0]);
	*splitsize = 2;
	return (argv);
}

static char	**malloc_location(t_vars *v, size_t *splitsize)
{
	char **locations;

	if (!find_env(v, "PATH", 0))
		locations = invalid_path(v, splitsize);
	else
		locations = ft_split_multi(find_env(v, "PATH", 0)->content, ":", \
			splitsize);
	return (locations);
}

static int	loop_locations(t_vars *v, char **new_path, char *command)
{
	char	**locations;
	size_t	splitsize;
	int		ret;
	int		i;

	i = 0;
	ret = FILENOTFOUND;
	locations = malloc_location(v, &splitsize);
	if (!locations)
		return (FILEERROR);
	while (locations[i])
	{
		ret = searchdir(locations[i], command);
		if (ret == FILEFOUND)
		{
			*new_path = ft_strdup(locations[i]);
			break ;
		}
		if (ret == FILEERROR)
			return (ret);
		i++;
	}
	ft_free_array((void**)locations, splitsize);
	return (ret);
}

static int	looper(t_vars *v, char **newpath, char *command)
{
	char		*path;
	char		*totalpath;
	int			ret;
	size_t		length;

	ret = loop_locations(v, &path, command);
	if (ret == FILENOTFOUND || ret == FILEERROR)
		return (ret);
	length = ft_strlen(path) + 1 + ft_strlen(command) + 1;
	totalpath = ft_calloc(length, sizeof(char));
	if (!totalpath)
		return (FILEERROR);
	ft_strlcat(totalpath, path, length + 1);
	ft_strlcat(totalpath, "/", length + 1);
	ft_strlcat(totalpath, command, length + 1);
	*newpath = totalpath;
	free(path);
	return (ret);
}

int			handle_static(t_vars *v, char **newpath, char *command)
{
	int ret;

	if (ft_strncmp(command, "/", 1))
	{
		ret = looper(v, newpath, command);
		if (ret == FILEERROR)
			return (FILEERROR);
	}
	else
	{
		*newpath = ft_strdup(command);
		if (!*newpath)
			return (FILEERROR);
	}
	ret = validate_file(*newpath);
	if (ret == FILEFOUND)
		return (FILEFOUND);
	if (ret == FILEPERMISSIONS)
		ft_printerror(command, EACCES);
	free(*newpath);
	return (ret);
}
