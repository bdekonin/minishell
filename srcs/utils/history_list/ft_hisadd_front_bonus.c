/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 12:26:08 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/23 16:26:04 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

void	his__ft_lstadd_front(t_history **alst, t_history *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}
