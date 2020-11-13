/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmdadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 12:26:08 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/11 16:52:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd__ft_lstadd_front(t_cmd **alst, t_cmd *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

