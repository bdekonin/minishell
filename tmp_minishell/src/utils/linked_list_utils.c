/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 20:11:14 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/12 16:41:49 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_new_env_var(t_vars *v, char *name, char *content)
{
	t_list	*new;
	t_env	*node;
	
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		ft_exit_error(v, EXIT_FAILURE);
	node->name = name;
	node->content = content;
	new = ft_lstnew(node);
	if (!new)
		ft_exit_error(v, EXIT_FAILURE);
	ft_lstadd_back(&v->env, new);
}

void	create_new_token(t_vars *v, const char *ptr, size_t len)
{
	t_list	*new;
	char	*str;

	str = ft_substr(ptr, 0, len); 
	if (!str)
		ft_exit_error(v, EXIT_FAILURE);
	new = ft_lstnew(str);
	if (!new)
		ft_exit_error(v, EXIT_FAILURE);
	ft_lstadd_back(&v->cmd, new);
}

t_list	*get_prev_node(t_vars *v, t_list *dst)
{
	t_list *tmp;
	
	if (dst == v->cmd)
		return (NULL);
	tmp = v->cmd;
	while (tmp)
	{
		if (tmp->next == dst)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_lst_remove_one(t_list **head, t_list *node)
{
	t_list *tmp;
	t_list *prev;
	
	if (node == *head)
	{
		*head = (*head)->next;
		ft_free(node->content);
		ft_free(node);
		return ;
	}
	tmp = (*head)->next;
	prev = *head;
	while (tmp)
	{
		if (tmp == node)
		{
			prev->next = tmp->next;
			ft_free(tmp->content);
			ft_free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
