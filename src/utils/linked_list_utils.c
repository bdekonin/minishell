/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 20:11:14 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/29 22:27:21 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_new_env_var(t_vars *v, char *name, char *content, \
				int checkmalloc)
{
	t_env	*node;

	if (checkmalloc == 1)
	{
		malloc_check(v, name);
		malloc_check(v, content);
	}
	node = env__ft_lstnew(name, content);
	malloc_check(v, node);
	env__ft_lstadd_back(&v->env, node);
}

void	function_src(char *src)
{
	size_t i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '\'')
			i += skip_quotations(src + i, src[i]);
		else if (src[i] == '\"')
			i += skip_quotations(src + i, src[i]);
		if (src[i] == ' ')
			src[i] = CHAR_SPECIAL_CHAR;
		i++;
	}
}

void	create_new_token(t_vars *v, const char *ptr, size_t len)
{
	t_list	*new;
	char	*str;

	str = ft_substr(ptr, 0, len);
	malloc_check(v, str);
	function_src(str);
	new = ft_lstnew(str);
	malloc_check(v, new);
	ft_lstadd_back(&v->tempcmd, new);
}

t_list	*get_prev_node(t_vars *v, t_list *dst)
{
	t_list *tmp;

	if (dst == v->tempcmd)
		return (NULL);
	tmp = v->tempcmd;
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
