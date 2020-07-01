/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 11:26:10 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/07/01 00:00:30 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct	s_list
{
	char		conversion;
	int			n_flags;
	int			min_width;
	int			prec;
	int			just;
	int			neg;
	char		pad_type;
	int			padding;
	int			pad_prec;
	char		*bstr;
	int			len_bstr;
	char		*fstr;
	int			len_fstr;
}				t_list;

int				ft_printf(const char *fmt, ...);
int				format_char(t_list *flags, char c);
int				format_str(t_list *flags);
int				format_int(t_list *flags);
t_list			*init_flags(const char *str, va_list argp);
char			*ft_itoa(int n, t_list *flags);
char			*ft_uitoa(unsigned int n, t_list *flags);
char			*ft_uitohex(unsigned int n, t_list *flags);
char			*ft_ptr(unsigned long long n, t_list *flags);
int				ft_printf_strlen(const char *str);
int				ft_putstr(t_list *flags);
char			*ft_printf_strdup(const char *s1);
int				ft_atoi(const char *str);
int				ft_csearch(char c, char *str);
int				ft_strsearchh(const char *s1, char *s2);
int				free_struct(t_list *flags);
int				format_int_left(t_list *flags);
int				format_int_right(t_list *flags);

#endif
