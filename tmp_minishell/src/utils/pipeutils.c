/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeutils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 23:17:33 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/01 10:44:58 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list *lastpipe(t_list *headptr)
{
	t_list *last;

	last = headptr;
	while (headptr)
	{
		if (is_pipe(headptr->content))
			last = headptr;
		headptr = headptr->next;
	}
	return (last->next);
}

t_list *firstpipe(t_list *headptr)
{
	while(headptr)
	{
		if (headptr->next && is_pipe(headptr->next->content))
			return(headptr);
		headptr = headptr->next;
	}
	return (NULL);
}