/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmdlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:38:32 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/11 16:52:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd	*cmd__ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
