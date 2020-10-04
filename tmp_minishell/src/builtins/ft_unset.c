/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 11:05:24 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/14 16:31:51 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void env__ft_lstremove_middle(char *name, t_list *new)
{
	t_list	*back;
	t_env	*node;
	//t_env *back;

	while (new)
	{
		node = new->content;
		if (!ft_strncmp(name, node->name, ft_strlen(node->name) + 1))
		{
			back->next = new->next;
			free(node->name);
			free(node->content);
			free(node);
			break ;
		}
		back = new;
		new = new->next;
	}
}

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
//	if (!sethistory(&v->history_head, v->line, "1"))
//		return (0);
	(void)(params);
//	(void)(cmd);
	return (1);
}