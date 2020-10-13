/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_int.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 16:18:47 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/07/21 19:54:08 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	find_len_fstr(t_list *flags)
{
	flags->len_bstr = ft_printf_strlen(flags->bstr);
	if (flags->prec > flags->len_bstr)
		flags->len_fstr = flags->prec;
	else if (flags->prec == 0 && flags->len_bstr == 1 && flags->bstr[0] == '0')
	{
		flags->len_fstr = 0;
		flags->bstr[0] = ' ';
	}
	else
		flags->len_fstr = flags->len_bstr;
	flags->len_fstr += flags->neg;
	if (flags->min_width > flags->len_fstr)
	{
		flags->padding = flags->min_width - flags->len_fstr;
		flags->len_fstr += flags->padding;
	}
	if (flags->prec < 0)
		flags->prec = 0;
	else if (flags->prec > flags->len_bstr)
		flags->pad_prec = flags->prec - flags->len_bstr;
}

int			format_int(t_list *flags)
{
	find_len_fstr(flags);
	flags->fstr = ft_calloc2((flags->len_fstr + 1), sizeof(char));
	if (!flags->fstr)
	{
		free(flags->bstr);
		return (0);
	}
	if (flags->just == 1)
		format_int_left(flags);
	else
		format_int_right(flags);
	free(flags->bstr);
	return (1);
}
