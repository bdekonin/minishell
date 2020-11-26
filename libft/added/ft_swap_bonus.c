/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_swap_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 12:02:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/26 19:03:03 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_swap(char **a, char **b)
{
	char *tmp_a;

	tmp_a = *a;
	*a = *b;
	*b = tmp_a;
}
