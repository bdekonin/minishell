/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 15:25:54 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 17:58:32 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	node__ft_lstclear(t_node **lst, void (*del)(void*))
{
	t_node		*tmp;

	if (!lst)
		return ;
	if (del)
		while (*lst)
		{
			tmp = (*lst)->next;
			node__ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	*lst = NULL;
}
