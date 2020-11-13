/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 10:46:37 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/11 10:27:44 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;
	size_t			len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dst = ft_calloc((len + 1), sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	return (dst);
}
