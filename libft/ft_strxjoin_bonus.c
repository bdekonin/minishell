/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strxjoin_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/21 12:21:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/06/10 13:36:06 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static char	*concat_strings(char **ptrs, size_t args, size_t len)
{
	char	*dst;
	size_t	i;

	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (0);
	i = 0;
	while (i < args)
	{
		if (ptrs[i])
			ft_strlcat(dst, ptrs[i], len + 1);
		i++;
	}
	return (dst);
}

char		*ft_strxjoin(size_t args, ...)
{
	va_list list;
	char	**ptrs;
	char	*dst;
	size_t	len;
	size_t	i;

	if (args == 0)
		return (0);
	va_start(list, args);
	i = 0;
	len = 0;
	ptrs = ft_calloc(args + 1, sizeof(char *));
	if (!ptrs)
		return (0);
	while (i < args)
	{
		ptrs[i] = va_arg(list, char *);
		if (ptrs[i])
			len += ft_strlen(ptrs[i]);
		i++;
	}
	va_end(list);
	dst = concat_strings(ptrs, args, len);
	free(ptrs);
	return (dst);
}
