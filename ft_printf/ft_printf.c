/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 14:53:01 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/05/17 19:35:17 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_vdprintf(int fd, const char *fmt, va_list argp)
{
	t_list		*flags;

	flags = 0;
	return (read_fmt(fmt, argp, flags));
}

int		ft_printf(const char *fmt, ...)
{
	va_list		argp;
	int			ret;

	va_start(argp, fmt);
	ret = ft_dprintf(1, fmt, argp);
	va_end(argp);
	return (ret);
}

int		ft_dprintf(int fd, const char *fmt, ...)
{
	va_list		argp;
	int			ret;

	va_start(argp, fmt);
	ret = ft_dprintf(fd, fmt, argp);
	va_end(argp);
	return (ret);
}
