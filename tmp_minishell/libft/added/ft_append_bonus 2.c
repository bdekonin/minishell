/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_append_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/09 20:45:32 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/22 12:12:25 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

char	*ft_append(char *s1, const char *s2)
{
	char	*dst;
	size_t	len;

	if (!s1)
	{
		s1 = ft_strdup("\0");
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcat(dst, s1, len + 1);
	ft_strlcat(dst, s2, len + 1);
	free(s1);
	return (dst);
}
