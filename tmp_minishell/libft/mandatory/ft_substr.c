/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 09:38:52 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/11 10:27:58 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;
	size_t			n;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	if (n - start < len)
		len = n - start;
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && start < n)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	return (substr);
}
