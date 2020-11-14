/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strxjoin_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/21 12:21:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/07 00:12:30 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>

/*
**		Multiple argument strings will be combined into a single string.
**		Last parameter of the function call should always be NULL.
**		E.g.:	str = ft_strxjoin("folder", "/", folder", "/", "file", NULL);
*/

static size_t	get_len(const char *src, va_list list)
{
	size_t	len;
	va_list	copy;

	len = 0;
	va_copy(copy, list);
	while (src)
	{
		len = len + ft_strlen(src);
		src = va_arg(copy, char *);
	}
	va_end(copy);
	return (len);
}

char			*ft_strxjoin(const char *src, ...)
{
	char	*dst;
	va_list	list;
	size_t	len;

	if (!src)
		return (NULL);
	va_start(list, src);
	len = get_len(src, list);
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	while (src)
	{
		ft_strlcat(dst, src, len + 1);
		src = va_arg(list, char *);
	}
	va_end(list);
	return (dst);
}
