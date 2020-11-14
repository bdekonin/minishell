/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_array_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 11:12:42 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/06 23:31:14 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

void	ft_print_array(char **array)
{
	size_t i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_putchar_fd('[', 1);
		ft_putnbr_fd((int)i, 1);
		ft_putstr_fd("] ", 1);
		ft_putendl_fd(array[i], 1);
		i++;
	}
}
