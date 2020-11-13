/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 14:32:23 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/08/09 21:08:41 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (!d && !s)
		return (NULL);
	while (i < len && d > s)
		i++;
	while (i > 0 && d > s)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
	while (i < len && d < s)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
