/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_prefix.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 08:16:31 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/08 16:42:53 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_prefix(t_vars *v)
{
	ft_printf(v->prefix, v->default_logname->content, \
		ft_strrchr(v->current_path, '/') + 1);	
}

void	resize_str(t_vars *v, char **str1, char *str2)
{
	*str1 = ft_append(*str1, "*");
	if (!*str1)
		ft_exit_error(v, EXIT_FAILURE);
	*str1 = ft_append(*str1, str2);
	if (!*str1)
		ft_exit_error(v, EXIT_FAILURE);
}
