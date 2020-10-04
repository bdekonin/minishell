/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getline_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 22:45:17 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/22 11:54:33 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

static int	read_file(int fd, char **line, char *buffer)
{
	int ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret > 0)
	{
		buffer[ret] = '\0';
		*line = ft_append(*line, buffer);
		if (!*line)
			return (-1);
	}
	else if (ret < 0)
		return (ft_free_ret_int(line, -1));
	return (ret);
}

int			ft_getline(int fd, char **line)
{
	int		ret;
	char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	*line = ft_strdup("\0");
	if (!*line)
		return (-1);
	ret = 1;
	while (ret > 0)
		ret = read_file(fd, line, buffer);
	return (ret);
}
