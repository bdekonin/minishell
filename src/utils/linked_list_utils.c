/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 20:11:14 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/13 21:52:39 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_new_env_var(t_vars *v, char *name, char *content)
{
	t_list	*new;
	t_env	*node;
	
	node = ft_calloc(1, sizeof(t_env));
	malloc_check(v, node);
	node->name = name;
	node->content = content;
	new = ft_lstnew(node);
	malloc_check(v, new);
	ft_lstadd_back(&v->env, new);
}
size_t	skip_quotations(const char *cli, char quotation_type);

// echo 
void test(char *src)
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
			src[i] = '*';
		i++;
	}
}

void	create_new_token(t_vars *v, const char *ptr, size_t len)
{
	t_list	*new;
	char	*str;

	str = ft_substr(ptr, 0, len);
	malloc_check(v, str);
	test(str);
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
