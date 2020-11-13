/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmddelone_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 12:51:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/11 19:28:30 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd__ft_lstdelone(t_cmd *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->line);
	free(lst);
	lst = NULL;
}
