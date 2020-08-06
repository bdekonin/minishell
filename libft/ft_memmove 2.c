/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 10:37:57 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/10 20:46:31 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** first it does the basic stuff till line 33
** then it looks if it overlaps, if len bigger then dest - source,
** then its false.
** then i is len set to the length of i minus one for null terminator.
** if it doesnt overlap then it just uses memcpy.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*source;

	dest = dst;
	source = (char*)src;
	if (src == NULL && dst == NULL)
		return (dst);
	if (len > (size_t)dest - (size_t)source)
	{
		i = len - 1;
		while ((int)i >= 0)
		{
			dest[i] = source[i];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
