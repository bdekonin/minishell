/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 15:40:26 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/06 21:39:29 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*list;

	if (!new)
		return ;
	list = *alst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		ft_lstadd_front(alst, new);
}
