/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:36:51 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/08 18:42:28 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_env(t_vars *v, char **params)
{
	t_env		*node;

	node = v->env;
	while (node)
	{
		if (node->content)
		{
			ft_putstr_fd(node->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(node->content, 1);
		}
		node = node->next;
	}
	return (0);
	(void)params;
}
