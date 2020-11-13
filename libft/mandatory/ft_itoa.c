/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 08:53:21 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/11 10:26:48 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		putnbr(char *str, size_t i, int n)
{
	if (n >= 10)
		putnbr(str, i - 1, n / 10);
	str[i] = n % 10 + 48;
}

static size_t	find_len(int n)
{
	size_t len;

	if (n == -2147483648)
		return (11);
	len = 1;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = find_len(n);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (n == -2147483648)
	{
		str[10] = '8';
		n = -214748364;
		len--;
	}
	if (n < 0)
	{
		n = n * -1;
		str[0] = '-';
	}
	putnbr(str, len - 1, n);
	return (str);
}
