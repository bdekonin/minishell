/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_prefix.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 20:25:36 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/09 20:28:35 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_prefix(t_vars *v)
{
	ft_printf(v->prefix, v->default_logname->content, \
		ft_strrchr(v->current_path, '/') + 1);	
}
