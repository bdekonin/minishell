/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_char.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 13:09:12 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/05/17 19:37:56 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pad_min_width(t_list *flags)
{
	while (flags->padding > 0)
	{
		if (write(flags->fd, &flags->pad_type, 1) != 1)
			return (0);
		flags->padding--;
	}
	return (1);
}

int			format_char(t_list *flags, char c)
{
	if (flags->min_width > 1)
	{
		flags->padding = flags->min_width - 1;
		flags->len_fstr = flags->min_width;
	}
	else
		flags->len_fstr = 1;
	if (flags->just == 0 && flags->padding > 0)
	{
		if (!pad_min_width(flags))
			return (0);
	}
	if (write(flags->fd, &c, 1) != 1)
		return (0);
	if (flags->just == 1 && flags->padding > 0)
	{
		if (!pad_min_width(flags))
			return (0);
	}
	return (1);
}
