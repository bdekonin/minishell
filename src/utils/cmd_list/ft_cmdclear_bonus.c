/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmdclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 15:25:54 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/11 19:27:43 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd__ft_lstclear(t_cmd **lst, void (*del)(void*))
{
	t_cmd		*tmp;
	
	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		cmd__ft_lstdelone(tmp, *del);
	}
	*lst = 0;
}
