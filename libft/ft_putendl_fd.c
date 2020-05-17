/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 16:25:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/23 13:01:39 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putendl_fd(char *s, int fd)
{
	int ret;

	if (!s)
		return (-1);
	ret = ft_putstr_fd(s, fd);
	if (write(fd, "\n", 1) < 0)
		ret = -1;
	else
		ret += 1;
	return (ret);
}
