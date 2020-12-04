/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_reduce_spaces.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:34:25 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/04 14:27:34 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*free_ptrs(char **arr, size_t size)
{
	ft_free_array((void **)arr, size);
	return (NULL);
}

static char	*concatenate_strings(char *dst, char *s2)
{
	char *tmp;

	tmp = ft_strxjoin(dst, STRING_SPECIAL_CHAR, s2, NULL);
	ft_free(dst);
	return (tmp);
}

char		*ft_reduce_spaces(const char *str, size_t size, size_t i)
{
	char	**arr;
	char	*dst;
	char	*tmp;

	arr = ft_split_multi(str, " ", &size);
	if (!arr)
		return (NULL);
	if (*str == ' ')
		dst = ft_strjoin(STRING_SPECIAL_CHAR, arr[i]);
	else
		dst = ft_strdup(arr[i]);
	if (!dst)
		return (free_ptrs(arr, size));
	i++;
	while (arr[i] != NULL)
	{
		tmp = concatenate_strings(dst, arr[i]);
		if (!tmp)
			return (free_ptrs(arr, size));
		dst = tmp;
		i++;
	}
	ft_free_array((void **)arr, size);
	return (dst);
}
