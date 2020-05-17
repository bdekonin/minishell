/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_swap_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/12 13:10:33 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/10 20:49:17 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(double *xp, double *yp)
{
	double temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}
