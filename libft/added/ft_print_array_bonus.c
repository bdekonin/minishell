/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_array_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 11:12:42 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/11 10:23:22 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>

void		ft_print_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		write(1, array[i], ft_strlen(array[i]));
		write(1, "\n", 1);
		i++;
	}
}
