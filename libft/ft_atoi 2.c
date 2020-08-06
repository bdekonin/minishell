/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 14:18:39 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/23 10:32:05 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int ans;
	long long int check;

	ans = 0;
	check = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		check = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		if (ans * 10 + *str - 48 < ans)
		{
			ans = (-1 * check - 1) / 2;
			return (ans * check);
		}
		ans = (ans * 10) + *str - 48;
		str++;
	}
	return (ans * check);
}
