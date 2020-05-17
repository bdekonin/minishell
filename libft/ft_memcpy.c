/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 15:20:21 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/26 21:40:25 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ptr1;
	char		*ptr2;

	ptr1 = (char*)src;
	ptr2 = (char*)dst;
	i = 0;
	if (!ptr1 && !ptr2)
		return (NULL);
	while (i < n)
	{
		ptr2[i] = ptr1[i];
		i++;
	}
	return (ptr2);
}
