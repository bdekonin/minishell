/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:43:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/23 16:39:00 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

void	his__ft_lstadd_back(t_history **alst, t_history *new)
{
	t_history *last;

	if (!new)
		return ;
	if (*alst)
	{
		last = his__ft_lstlast(*alst);
		last->next = new;
	}
	else
		his__ft_lstadd_front(alst, new);
}
