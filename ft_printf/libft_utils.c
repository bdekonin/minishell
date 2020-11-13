/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:57:38 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 10:51:31 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_printf_putstr(t_list *flags)
{
	if (write(1, flags->fstr, flags->len_fstr) != flags->len_fstr)
	{
		free(flags->fstr);
		return (0);
	}
	return (1);
}

char	*ft_printf_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*dest;

	if (!s1)
		s1 = "(null)";
	len = ft_printf_strlen(s1);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_printf_atoi(const char *str)
{
	unsigned long long	result;
	int					neg;
	int					i;

	result = 0;
	i = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		neg = neg * -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	result = result * neg;
	return (result);
}
