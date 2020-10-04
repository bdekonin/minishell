/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atod_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 17:30:08 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/08/24 12:28:35 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static double	read_decimals(const char *str)
{
	double result;
	double magnitude;
	size_t i;

	result = 0;
	magnitude = 1;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		magnitude = magnitude * 10;
		i++;
	}
	result = result / magnitude;
	return (result);
}

double			ft_atod(const char *str)
{
	double	result;
	int		neg;
	size_t	i;

	result = 0;
	neg = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	if (str[i] == '.')
		result += read_decimals(str + i + 1);
	result = result * neg;
	return (result);
}
