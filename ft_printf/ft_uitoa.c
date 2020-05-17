/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uitoa.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 10:25:11 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/01/20 11:39:01 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putnbr(char *str, int i, unsigned int n)
{
	if (n >= 10)
		putnbr(str, i - 1, n / 10);
	str[i] = n % 10 + 48;
}

static int	find_len(unsigned int n)
{
	int len;

	len = 1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_uitoa(unsigned int n, t_list *flags)
{
	int		len;
	char	*str;

	len = find_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	flags->neg = 0;
	str[len] = '\0';
	putnbr(str, len - 1, n);
	return (str);
}
