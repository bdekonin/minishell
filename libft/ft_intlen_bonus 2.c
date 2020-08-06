/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intlen_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 10:44:09 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/06 13:57:41 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(long long n, int base)
{
	int count;

	count = 1;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= base;
		count++;
	}
	return (count);
}
