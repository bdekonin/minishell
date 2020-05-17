/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_int_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 20:08:41 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/01/24 16:00:16 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	negative(t_list *flags, int i)
{
	if (flags->neg == 1)
	{
		flags->fstr[i] = '-';
		i++;
	}
	return (i);
}

static int	min_width(t_list *flags, int i)
{
	while (flags->padding > 0)
	{
		flags->fstr[i] = flags->pad_type;
		i++;
		flags->padding--;
	}
	return (i);
}

static int	precision(t_list *flags, int i)
{
	while (flags->pad_prec > 0)
	{
		flags->fstr[i] = '0';
		i++;
		flags->pad_prec--;
	}
	return (i);
}

int			format_int_left(t_list *flags)
{
	int i;
	int j;

	i = 0;
	i = negative(flags, i);
	i = precision(flags, i);
	j = 0;
	while (flags->bstr[j] != '\0')
	{
		flags->fstr[i] = flags->bstr[j];
		i++;
		j++;
	}
	i = min_width(flags, i);
	flags->fstr[i] = '\0';
	return (1);
}

int			format_int_right(t_list *flags)
{
	int i;
	int j;

	i = 0;
	if (flags->pad_type == '0')
		i = negative(flags, i);
	i = min_width(flags, i);
	if (flags->pad_type == ' ')
		i = negative(flags, i);
	i = precision(flags, i);
	j = 0;
	while (flags->bstr[j] != '\0')
	{
		flags->fstr[i] = flags->bstr[j];
		i++;
		j++;
	}
	flags->fstr[i] = '\0';
	return (1);
}
