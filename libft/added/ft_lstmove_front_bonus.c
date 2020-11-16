/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmove_front_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 23:16:49 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/09 08:16:38 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
**		Moves an element in a list to the front of the same list
**		and sets the previous element to point to the next element.
*/

void	ft_lstmove_front(t_list **head, t_list *node)
{
	t_list *tmp;

	if (!node || !*head || !(*head)->next || node == *head)
		return ;
	tmp = *head;
	while (tmp->next)
	{
		if (tmp->next == node)
		{
			tmp->next = node->next;
			break ;
		}
		tmp = tmp->next;
	}
	node->next = *head;
	*head = node;
}
