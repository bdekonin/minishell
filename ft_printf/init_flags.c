/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_flags.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/11 15:21:30 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/01/23 19:33:35 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	read_padding_type(const char *str, t_list *flags)
{
	int i;

	i = 0;
	while (i < flags->n_flags && str[i] != '\0')
	{
		if (str[i] == '0' && str[i - 1] != '.')
		{
			if (str[i - 1] >= 49 && str[i - 1] <= 57)
				return (' ');
			if (flags->prec >= 0)
				return (' ');
			if (flags->just == 1)
				return (' ');
			return ('0');
		}
		i++;
	}
	return (' ');
}

static int	read_justifier(const char *str, t_list *flags)
{
	int i;

	i = 0;
	while (i < flags->n_flags && str[i] != '\0')
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

static int	read_precision(const char *str, t_list *flags, va_list argp)
{
	int i;

	i = 0;
	while (i < flags->n_flags && str[i] != '\0')
	{
		if (str[i] == '.')
		{
			i++;
			while (str[i] == '.')
				i++;
			if (str[i] == '*')
				return (va_arg(argp, int));
			else if (str[i] >= 48 && str[i] <= 57)
				return (ft_atoi((char *)str + i));
			else
				return (0);
		}
		i++;
	}
	return (-1);
}

static int	read_minwidth(const char *str, t_list *flags, va_list argp)
{
	int i;
	int n;

	i = 0;
	while (i < flags->n_flags && str[i] != '\0')
	{
		if (str[i] == '.')
			return (0);
		if (str[i] == '*' && str[i - 1] != '.')
		{
			n = va_arg(argp, int);
			if (n < 0)
			{
				flags->just = 1;
				return (n * -1);
			}
			return (n);
		}
		if (str[i] >= 49 && str[i] <= 57 && str[i - 1] != '.')
			return (ft_atoi((char *)str + i));
		i++;
	}
	return (0);
}

t_list		*init_flags(const char *str, va_list argp)
{
	t_list	*flags;
	int		i;

	flags = malloc(1 * sizeof(t_list));
	if (!flags)
		return (0);
	i = ft_strsearch(str, "cspdiuxX%");
	flags->conversion = str[i];
	flags->n_flags = i;
	flags->just = read_justifier(str, flags);
	flags->min_width = read_minwidth(str, flags, argp);
	flags->prec = read_precision(str, flags, argp);
	flags->pad_type = read_padding_type(str, flags);
	flags->padding = 0;
	flags->pad_prec = 0;
	return (flags);
}
