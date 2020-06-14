/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc_2d_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 17:53:13 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/12 18:04:10 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_calloc_2d(size_t width, size_t height)
{
	char **array;
	size_t i;

	i = 0;
	array = ft_calloc(height + 1, sizeof(char*));
	if (!array)
		return (NULL);
	while (i < height)
	{
		array[i] = ft_calloc(width, sizeof(char));
		if (!array[i])
		{
			ft_free_array((void*)array, i - 1);
			return (NULL);
		}
		i++;
	}
	return (array);
}
