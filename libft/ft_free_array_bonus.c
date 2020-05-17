/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/16 23:38:48 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/16 23:39:06 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(void **ptr, int size)
{
	while (size > 0)
	{
		size--;
		free(ptr[size]);
	}
	free(ptr);
}