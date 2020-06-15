/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 12:26:08 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 17:58:15 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	node__ft_lstadd_front(t_node **alst, t_node *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}
