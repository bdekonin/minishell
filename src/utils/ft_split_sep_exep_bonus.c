/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_sep_exep_bonus.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 08:58:49 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/04 14:43:41 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_strings(const char *src, char *sep)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (ft_strlen(sep) == 0 && src[i] != '\0')
		return (1);
	while (src[i] != '\0')
	{
		if (!ft_charsearch(src[i], sep))
		{
			count++;
			i += get_len_split(src, sep, i);
		}
		i = get_start_split(src, sep, i);
	}
	return (count);
}

static int		init_dst(char **dst, const char *src, char *sep, size_t size)
{
	size_t i;
	size_t start;
	size_t len;

	i = 0;
	start = 0;
	len = 0;
	while (i < size)
	{
		start = get_start_split(src, sep, start + len);
		len = get_len_split(src, sep, start);
		dst[i] = ft_substr(src, start, len);
		if (!dst[i])
		{
			ft_free_array((void **)dst, i);
			return (0);
		}
		i++;
	}
	return (1);
}

char			**ft_split_sep_exep(const char *src, char *sep, size_t *size)
{
	char	**dst;
	size_t	array_size;

	if (!src)
		return (NULL);
	array_size = count_strings(src, sep);
	dst = ft_calloc((array_size + 1), sizeof(char *));
	if (!dst)
		return (NULL);
	if (!init_dst(dst, src, sep, array_size))
		return (NULL);
	if (size)
		*size = array_size;
	return (dst);
}
