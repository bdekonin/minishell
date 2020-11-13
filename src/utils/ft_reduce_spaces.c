/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_reduce_spaces.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:34:25 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/27 10:43:40 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*free_ptrs(char **arr, size_t size)
{
    ft_free_array((void **)arr, size);
    return (NULL);
}

char 		*ft_reduce_spaces(const char *str)
{
	size_t	size;
	size_t	i;
	char	**arr;
	char	*dst;
	char	*tmp;

	size = 0;
	arr = ft_split_multi(str, " ", &size);
	if (!arr)
		return (NULL);
	dst = ft_strdup(arr[0]);
	if (!dst)
        return (free_ptrs(arr, size));
	i = 1;
	while (arr[i] != NULL)
	{
		tmp = ft_strxjoin(dst, " ", arr[i], NULL);
		ft_free(dst);
		if (!tmp)
		    return (free_ptrs(arr, size));
		dst = tmp;
		i++;
	}
	ft_free_array((void **)arr, size);
	return (dst);
}