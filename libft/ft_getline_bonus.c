/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getline_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:36:49 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/14 21:44:06 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_and_exit(char **line)
{
	free(*line);
	return (-1);
}

static char	*strjoin_and_free(char *s1, char *s2)
{
	char	*dst;
	size_t	i;
	size_t	len_1;
	size_t	len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	dst = ft_calloc(len_1 + len_2 + 1, sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len_1)
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	free(s1);
	while (i < len_2)
	{
		dst[len_1 + i] = s2[i];
		i++;
	}
	return (dst);
}

static int	read_file(int fd, char **line, char *buffer)
{
	int ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret > 0)
	{
		buffer[ret] = '\0';
		*line = strjoin_and_free(*line, buffer);
		if (!*line)
			return (free_and_exit(line));
	}
	else if (ret < 0)
		return (free_and_exit(line));
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
