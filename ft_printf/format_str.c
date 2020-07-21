/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_str.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 09:45:21 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/07/21 19:54:08 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	find_len_fstr(t_list *flags)
{
	flags->len_bstr = ft_printf_strlen(flags->bstr);
	if (flags->len_bstr > flags->prec && flags->prec >= 0 &&
		flags->conversion != '%')
		flags->len_fstr = flags->prec;
	else
	{
		flags->len_fstr = flags->len_bstr;
		flags->prec = flags->len_bstr;
	}
	if (flags->min_width > flags->len_fstr)
		flags->len_fstr = flags->min_width;
	flags->padding = flags->len_fstr - flags->prec;
}

static int	pad_min_width(t_list *flags, int i)
{
	while (flags->padding > 0)
	{
		flags->fstr[i] = flags->pad_type;
		i++;
		flags->padding--;
	}
	return (i);
}

int			format_str(t_list *flags)
{
	int i;
	int j;

	i = 0;
	j = 0;
	find_len_fstr(flags);
	flags->fstr = ft_calloc2((flags->len_fstr + 1), sizeof(char));
	if (!flags->fstr)
	{
		free(flags->bstr);
		return (0);
	}
	if (flags->just == 0)
		i = pad_min_width(flags, i);
	while (flags->bstr[j] != '\0' && j < flags->prec)
	{
		flags->fstr[i] = flags->bstr[j];
		i++;
		j++;
	}
	if (flags->just == 1)
		i = pad_min_width(flags, i);
	flags->fstr[flags->len_fstr] = '\0';
	free(flags->bstr);
	return (1);
}
