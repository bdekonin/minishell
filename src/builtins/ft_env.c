/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:36:51 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/27 16:21:36 by lverdoes      ########   odam.nl         */
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
			ft_printf("%s=%s\n", node->name, node->content);
		node = node->next;
	}
	return (0);
	(void)params;
}
