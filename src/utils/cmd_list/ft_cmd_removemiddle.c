/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmd_removemiddle.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 10:58:56 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/15 16:29:34 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd__removemiddle(t_cmd **head, t_cmd *remove)
{
	remove->prev->next = remove->next;
	remove->next->prev = remove->prev;
	remove->prev->type = remove->type;
	cmd__ft_lstdelone(remove, free);
}