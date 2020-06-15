/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:43:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 17:57:58 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	node__ft_lstadd_back(t_node **alst, t_node *new)
{
	t_node *last;

	if (!new)
		return ;
	if (*alst)
	{
		last = node__ft_lstlast(*alst);
		last->next = new;
	}
	else
		node__ft_lstadd_front(alst, new);
}
