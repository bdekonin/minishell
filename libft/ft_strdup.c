/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 10:31:37 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/23 11:58:20 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char		*ft_strdup(const char *s1)
{
	int		len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = ft_calloc(len + 1, sizeof(char));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, len);
	return (s2);
}
