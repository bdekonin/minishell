/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 08:22:37 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/07 22:39:38 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	get_start(char const *str, char c, size_t i)
{
	while (str[i] != '\0' && str[i] == c)
		i++;
	return (i);
}

static size_t	get_len(char const *str, char c, size_t start)
{
	size_t i;
	size_t len;

	i = start;
	len = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static size_t	count_str(char const *str, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (c == '\0' && str[i] != '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		while (str[i] == c)
			i++;
	}
	return (count);
}

static char		**init_dst(char const *s, char c, size_t count, char **dst)
{
	size_t i;
	size_t start;
	size_t len;

	i = 0;
	start = 0;
	len = 0;
	while (i < count)
	{
		start = get_start(s, c, start + len);
		len = get_len(s, c, start);
		dst[i] = ft_substr(s, start, len);
		if (!dst[i])
		{
			while (i > 0)
			{
				i--;
				ft_free(dst[i]);
			}
			ft_free(dst);
			return (NULL);
		}
		i++;
	}
	return (dst);
}

char			**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	size;

	if (!s)
		return (NULL);
	size = count_str(s, c);
	dst = ft_calloc(size + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	dst = init_dst(s, c, size, dst);
	return (dst);
}
