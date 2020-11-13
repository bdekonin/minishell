/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_array_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 13:42:00 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/24 11:55:40 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_free_array(void **array, size_t i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
	return (0);
}

int		ft_free_ret_int(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

void	*ft_free_ret_ptr(void *ptr, void *ret)
{
	free(ptr);
	return (ret);
}

int		ft_free(void *ptr)
{
	free(ptr);
	return (0);
}
