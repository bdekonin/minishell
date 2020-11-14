/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstremove_one_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 21:05:30 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/09 08:16:55 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**		Removes and frees an element from a list and sets the previous element
**		to point to the next element.
*/

void	ft_lstremove_one(t_list **head, t_list *node, void (*del)(void *))
{
	t_list *tmp;
	t_list *prev;

	if (!*head || !node)
		return ;
	if (node == *head)
	{
		*head = (*head)->next;
		ft_lstdelone(node, del);
		return ;
	}
	prev = *head;
	tmp = (*head)->next;
	while (tmp)
	{
		if (tmp == node)
		{
			prev->next = tmp->next;
			ft_lstdelone(tmp, del);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
