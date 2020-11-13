/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 15:51:49 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/22 11:58:07 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>
#include <limits.h>

static char		*reset_ptr(char **str, int fd)
{
	char	*tmp;
	char	*dst;
	size_t	i;

	i = ft_substrlen(str[fd], "\n");
	dst = ft_substr(str[fd], 0, i);
	if (!dst)
		return (ft_free_ret_ptr(str[fd], NULL));
	tmp = str[fd];
	str[fd] = ft_strdup(str[fd] + i + 1);
	ft_free(tmp);
	return (dst);
}

static int		read_file(int fd, char **str)
{
	int		ret;
	char	buffer[BUFFER_SIZE + 1];

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret < 0)
		return (ft_free_ret_int(str[fd], -1));
	buffer[ret] = '\0';
	str[fd] = ft_append(str[fd], buffer);
	if (!str[fd])
		return (-1);
	if (ret == 0)
		return (0);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	int			ret;
	static char	*str[OPEN_MAX];

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strdup("\0");
	if (!str[fd])
		return (-1);
	ret = 1;
	while (ret > 0 && !ft_strchr(str[fd], '\n'))
		ret = read_file(fd, str);
	if (ret < 0)
		return (-1);
	*line = reset_ptr(str, fd);
	if (!*line)
		return (-1);
	return (ret);
}
