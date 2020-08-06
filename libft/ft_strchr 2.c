/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 08:34:30 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/26 21:51:08 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	int		x;

	i = 0;
	str = (char*)s;
	x = ft_strlen(s);
	while (i < x + 1)
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (0);
}
