/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 15:25:54 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/23 16:39:06 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

void	his__ft_lstclear(t_history **lst, void (*del)(void*))
{
	t_history		*tmp;

	if (!lst)
		return ;
	if (del)
		while (*lst)
		{
			tmp = (*lst)->next;
			his__ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	*lst = NULL;
}
