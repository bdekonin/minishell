/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 10:49:51 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/23 12:50:57 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;
	char	*src;

	i = 0;
	if (!s)
		return (0);
	src = (char*)s;
	if ((size_t)start > ft_strlen(s) && src[0] != '\0')
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		dest = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (0);
	while (i < len && src[start + i] != '\0')
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
