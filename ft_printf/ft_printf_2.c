/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 14:53:01 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/05/17 19:38:02 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	alloc_conversion(const char *fmt, t_list *flags, int i, va_list argp)
{
	if (fmt[i] == '%')
		return (format_char(flags, '%'));
	if (fmt[i] == 'c')
		return (format_char(flags, va_arg(argp, int)));
	if (fmt[i] == 's')
		flags->bstr = ft_printf_strdup(va_arg(argp, char *));
	if (fmt[i] == 'p')
		flags->bstr = ft_ptr(va_arg(argp, unsigned long long), flags);
	if (fmt[i] == 'd' || fmt[i] == 'i')
		flags->bstr = ft_itoa(va_arg(argp, int), flags);
	if (fmt[i] == 'u')
		flags->bstr = ft_uitoa(va_arg(argp, unsigned int), flags);
	if (fmt[i] == 'x' || fmt[i] == 'X')
		flags->bstr = ft_uitohex(va_arg(argp, unsigned int), flags);
	if (!flags->bstr)
		return (0);
	return (1);
}

int	convert_arg(const char *fmt, t_list *flags, int i, va_list argp)
{
	if (!alloc_conversion(fmt, flags, i, argp))
		return (free_struct(flags));
	if (flags->conversion == 'c' || flags->conversion == '%')
		return (1);
	if (flags->conversion == 's' && !format_str(flags))
		return (free_struct(flags));
	if (ft_csearch(flags->conversion, "pdiuxX") > -1 && !format_int(flags))
		return (free_struct(flags));
	if (!ft_putstr(flags))
		return (free_struct(flags));
	free(flags->fstr);
	return (1);
}

int	read_fmt(const char *fmt, va_list argp, t_list *flags)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			flags = init_flags(fmt + i, argp);
			if (!flags)
				return (-1);
			i += flags->n_flags;
			if (!convert_arg(fmt, flags, i, argp))
				return (-1);
			ret += flags->len_fstr - 1;
			free(flags);
		}
		else if (write(flags->fd, fmt + i, 1) != 1)
			return (-1);
		ret++;
		i++;
	}
	return (ret);
}
