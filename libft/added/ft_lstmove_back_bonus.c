/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmove_back_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 23:16:51 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/09 08:16:32 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**		Moves an element in a list to the back of the same list
**		and sets the previous element to point to the next element.
*/

void	ft_lstmove_back(t_list **head, t_list *node)
{
	t_list *tmp;

	if (!node || !*head || !(*head)->next || !node->next)
		return ;
	tmp = *head;
	if (node == *head)
		*head = node->next;
	else
	{
		while (tmp->next)
		{
			if (tmp->next == node)
				tmp->next = node->next;
			tmp = tmp->next;
		}
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}
