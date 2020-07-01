/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nodeadd_back_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:43:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/01 14:12:32 by bdekonin      ########   odam.nl         */
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

void	cmd__ft_lstadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd *last;

	if (!new)
		return ;
	if (*alst)
	{
		last = cmd__ft_lstlast(*alst);
		last->next = new;
	}
	else
	{
		cmd__ft_lstadd_front(alst, new);
	}
}
