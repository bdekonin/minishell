/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 14:55:33 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/05/17 14:58:32 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(char *str, int i, unsigned long long n, t_list *flags)
{
	if (n >= 16)
		ft_puthex(str, i - 1, n / 16, flags);
	n = n % 16;
	if (n >= 10)
	{
		if (flags->conversion == 'X')
			str[i] = n + 55;
		else
			str[i] = n + 87;
	}
	else
		str[i] = n + 48;
}

static int	find_len(unsigned long long n)
{
	int len;

	len = 1;
	while (n >= 16)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

static char	*ft_ulltohex(unsigned long long n, t_list *flags)
{
	char	*str;
	int		len;

	len = find_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	flags->neg = 0;
	str[len] = '\0';
	ft_puthex(str, len - 1, n, flags);
	return (str);
}

static char	*concat_ptr(char *hex, int len)
{
	char	*str;
	int		i;
	int		j;

	str = malloc((len + 3) * sizeof(char));
	if (!str)
		return (0);
	str[0] = '0';
	str[1] = 'x';
	i = 2;
	j = 0;
	while (j < len && hex)
	{
		str[i] = hex[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_ptr(unsigned long long n, t_list *flags)
{
	char	*hex;
	char	*str;
	int		len;

	if (n == 0 && flags->prec == 0)
	{
		flags->neg = 0;
		str = concat_ptr("", 0);
		return (str);
	}
	hex = ft_ulltohex(n, flags);
	if (!hex)
		return (0);
	len = ft_printf_strlen(hex);
	str = concat_ptr(hex, len);
	free(hex);
	return (str);
}
