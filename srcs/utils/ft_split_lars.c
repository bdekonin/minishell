/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_lars.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 08:22:37 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/05/19 23:29:15 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static size_t	get_start(char const *str, char c, size_t start, size_t len)
{
	size_t i;

	i = start + len;
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

static char		**init_array(char const *s, char c, size_t count, char **array)
{
	size_t i;
	size_t start;
	size_t len;

	i = 0;
	start = 0;
	len = 0;
	while (i < count)
	{
		start = get_start(s, c, start, len);
		len = get_len(s, c, start);
		array[i] = ft_substr(s, start, len);
		if (!array[i])
		{
			while (i > 0)
			{
				i--;
				free(array[i]);
			}
			free(array);
			return (0);
		}
		i++;
	}
	return (array);
}

char			**ft_split_lars(char const *s, char c, int *lst_size)
{
	char	**array;
	size_t	count;

	if (!s)
		return (0);
	count = count_str(s, c);
	*lst_size = count;
	array = (char**)malloc((count + 1) * sizeof(char*));
	if (!array)
		return (0);
	array = init_array(s, c, count, array);
	if (array)
		array[count] = 0;
	return (array);
}
