/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hislast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:38:32 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 18:00:14 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

t_node	*node__ft_lstlast(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
