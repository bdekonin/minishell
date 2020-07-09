/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nodeclear_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 15:25:54 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/09 12:56:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	node__ft_lstclear(t_node **lst, void (*del)(void*))
{
	t_node		*tmp;

	tmp = *lst;
	if (!lst)
		return ;
	if (del)
		while (*lst)
		{
			tmp = (*lst)->next;
			node__ft_lstdelone(*lst, free);
			*lst = tmp;
		}
	*lst = NULL;
}

void	cmd__ft_lstclear(t_cmd **lst, void (*del)(void*))
{
	t_cmd		*tmp;

	if (!lst)
		return ;
	if (del)
		while (*lst)
		{
			tmp = (*lst)->next;
			cmd__ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	*lst = NULL;
}
