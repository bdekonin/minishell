/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 17:22:25 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/08/09 21:17:21 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!src)
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
