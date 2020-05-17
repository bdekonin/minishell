/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 16:02:37 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/23 12:43:16 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;

	i = ft_strlen(dst);
	j = 0;
	if (i < dstsize)
	{
		while (j < dstsize - i - 1 && src[j] != '\0')
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	while (src[j] != '\0')
		j++;
	if (dstsize <= i)
		return (dstsize + j);
	return (i + j);
}
