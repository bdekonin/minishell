/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisdelone_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 12:51:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/10 10:42:43 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

void	his__ft_lstdelone(t_history *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
	{
		del(lst->fullcommand);
		del(lst->ret);
	}
	free(lst);
}
