/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:17:12 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/04 14:02:20 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	**free_array(char **array, size_t i)
{
	while (i > 0)
	{
		i--;
		ft_free(array[i]);
	}
	ft_free(array);
	return (NULL);
}

static void	copy_ptrs(char **dst, char **src, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

char		**ft_realloc(char **src, const char *line, size_t *size)
{
	char	**dst;
	size_t	array_size;

	array_size = ft_array_size((const char **)src);
	dst = ft_calloc(array_size + 2, sizeof(char *));
	if (!dst)
		return (free_array(src, array_size));
	copy_ptrs(dst, src, array_size);
	ft_free(src);
	dst[array_size] = ft_strdup(line);
	if (!dst[array_size])
		return (free_array(dst, array_size));
	if (size)
		*size = array_size + 1;
	return (dst);
}
