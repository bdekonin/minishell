/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeutils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 23:17:33 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/12 21:13:05 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd *lastpipe(t_cmd *headptr)
{
	t_cmd *last;
	
	last = headptr;
	while (headptr)
	{
		if (headptr->type == PIPELINE)
			last = headptr;
		headptr = headptr->next;
	}
	return (last->next);
}

t_cmd *lastredir(t_cmd *headptr)
{
	t_cmd *last;
	
	last = headptr;
	while (headptr)
	{
		if (headptr->type >= 60 && headptr->type != PIPELINE)
			last = headptr;
		headptr = headptr->next;
	}
	return (last->next);
}