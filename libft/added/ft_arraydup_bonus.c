/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arraydup_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/13 11:59:09 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/05 19:45:37 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char		**free_array(char **array, size_t i)
{
	while (i > 0)
	{
		i--;
		ft_free(array[i]);
	}
	ft_free(array);
	return (NULL);
}

char			**ft_arraydup(const char **array)
{
	char	**dst;
	size_t	size;
	size_t	i;

	if (!array)
		return (NULL);
	size = ft_array_size(array);
	dst = ft_calloc((size + 1), sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = ft_strdup(array[i]);
		if (!dst[i])
			return (free_array(dst, i));
		i++;
	}
	return (dst);
}
