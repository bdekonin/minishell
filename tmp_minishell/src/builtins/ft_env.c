/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:36:51 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/14 16:42:43 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_vars *v, char **params)
{
	t_list	*tmp;
	t_env	*node;

	tmp = v->env;
	while (tmp)
	{
		node = tmp->content;
		ft_printf("%s=%s\n", node->name, node->content);
		tmp = tmp->next;
	}
//	if (!sethistory(&v->history_head, v->line, "1"))
//		return (0);
	(void)(params);
	return (1);
}
