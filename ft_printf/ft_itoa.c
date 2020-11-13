/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 10:23:47 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 10:49:52 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putnbr(char *str, int i, int n)
{
	if (n >= 10)
		putnbr(str, i - 1, n / 10);
	str[i] = n % 10 + 48;
}

static int	find_len(int n)
{
	int len;

	if (n == -2147483648)
		return (10);
	len = 1;
	if (n < 0)
		n = n * -1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_printf_itoa(int n, t_list *flags)
{
	int		len;
	char	*str;

	len = find_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n < 0)
		flags->neg = 1;
	else
		flags->neg = 0;
	str[len] = '\0';
	if (n == -2147483648)
	{
		str[9] = '8';
		n = 214748364;
		len--;
	}
	if (n < 0)
		n = n * -1;
	putnbr(str, len - 1, n);
	return (str);
}
