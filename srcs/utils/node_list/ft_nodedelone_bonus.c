/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nodedelone_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 12:51:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/02 11:11:24 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	node__ft_lstdelone(t_node *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
	{
		cmd__ft_lstclear(&lst->cmd, del);
	}
	free(lst);
}

void	cmd__ft_lstdelone(t_cmd *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
	{
		del(lst->line);
	}
	free(lst);
}
