/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 13:44:51 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/08 14:06:56 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_vars *v) //debug function
{
	t_list	*tmp;
	t_cmd	*node;

	tmp = v->cmd;
	while (tmp)
	{
		node = tmp->content;
		printf("[%s]", node->token);
		tmp = tmp->next;
		if (tmp)
			printf("-");
	}
	printf("\n");
}

void	ft_lst_remove_one_after(t_list **head, t_list *node)
{
	t_list *tmp;
	t_list *prev;
	
	prev = *head;
	while (prev)
	{
		if (prev == node)
		{
			tmp = prev->next;
			prev->next = tmp->next;
			ft_free(tmp->content);
			ft_free(tmp);
			return ;
		}
		prev = prev->next;
	}
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

int	is_redirection(t_list *tmp)
{
	t_cmd	*node;

	if (!tmp || !tmp->content)
		return (0);
	node = tmp->content;
	if (!ft_strncmp(node->token, ">>", 3) || \
		(!ft_strncmp(node->token, ">", 2)) || \
		(!ft_strncmp(node->token, "<", 2)))
		return (1);
	return (0);
}

int	is_pipe(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strncmp(arg, "|", 2))
		return (1);
	return (0);
}

int	is_semicolon(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strncmp(arg, ";", 2))
		return (1);
	return (0);
}

void	free_cmd_list(t_vars *v)
{
	t_list	*tmp;
	t_list	*prev;
	t_cmd	*node;

	tmp = v->cmd;
	while (tmp)
	{
		node = tmp->content;
		ft_free(node->token);
		ft_free(node);
		prev = tmp;
		tmp = tmp->next;
		ft_free(prev);
	}
	v->cmd = 0;
}

static size_t	get_counter(t_list *tmp)
{
	size_t	counter;
	t_cmd	*node;

	counter = 1;
	while (tmp)
	{
		node = tmp->content;
		if (!ft_strncmp(node->token, ";", 2))
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}

void		find_semicolons(t_vars *v)
{
	size_t	counter;
	size_t	i;
	t_list	*tmp;
	t_cmd	*node;

	counter = get_counter(v->cmd);
	v->cmd_ptr = ft_calloc(counter + 1, sizeof(t_list *));
	if (!v->cmd_ptr)
		ft_exit_error(v, EXIT_FAILURE);
	tmp = v->cmd;
	v->cmd_ptr[0] = tmp;
	i = 1;
	while (tmp && i < counter)
	{
		node = tmp->content;
		if (!ft_strncmp(node->token, ";", 2))
		{
			v->cmd_ptr[i] = tmp->next;
			i++;
		}	
		tmp = tmp->next;
	}
}
