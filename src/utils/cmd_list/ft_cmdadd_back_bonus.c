/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmdadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:43:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/11 16:52:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd__ft_lstadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd *last;

	if (!new)
		return ;
	if (*alst)
	{
		last = cmd__ft_lstlast(*alst);
		last->next = new;
		new->prev = last;
	}
	else
	{
		cmd__ft_lstadd_front(alst, new);
	}
}
