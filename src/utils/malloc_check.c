/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 19:06:48 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/23 21:56:51 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_check(t_vars *v, void *ptr)
{
	if (!ptr)
		ft_exit_error(v, EXIT_FAILURE, 1);
}
