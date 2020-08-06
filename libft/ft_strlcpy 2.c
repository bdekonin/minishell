/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 14:16:08 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/25 15:41:55 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (dst == 0 || src == 0)
		return (0);
	while (src[j] != '\0')
	{
		if (i < dstsize - 1 && dstsize > 0)
		{
			dst[i] = src[i];
			i++;
		}
		j++;
	}
	if (dstsize == 0)
		return (j);
	dst[i] = '\0';
	return (j);
}
