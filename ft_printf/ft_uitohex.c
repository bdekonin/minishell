/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uitohex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 10:27:02 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/01/24 15:15:07 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(char *str, int i, unsigned int n, t_list *flags)
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

static int	find_len(unsigned int n)
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

char		*ft_uitohex(unsigned int n, t_list *flags)
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
