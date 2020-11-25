/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmd_removemiddle.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 10:58:56 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/23 21:42:18 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int		cmd__removemiddle(t_cmd *remove, int ret)
{
	remove->prev->next = remove->next;
	remove->next->prev = remove->prev;
	remove->prev->type = remove->type;
	cmd__ft_lstdelone(remove, free);
	return (ret);
}
