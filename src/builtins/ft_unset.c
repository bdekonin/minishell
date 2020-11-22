/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 11:05:24 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/22 17:27:48 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// The return status is zero unless a name does not exist or is readonly.

int ft_unset(t_vars *v, char **params)
{
	size_t i;

	i = 0;
	while (params[i])
	{
		env__ft_lstremove_middle(params[i], v->env);
		i++;
	}
	return (0);
}