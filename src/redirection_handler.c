/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_handler.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 16:01:47 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/05 16:22:09 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			redirection_handler(t_vars *v, t_cmd *list)
{
	if (list && list->type >= 60 && list->type != PIPELINE)
	{
		if (mainredir(v, list->type, list->next->line) == 0)
			return (0);
	}
	if (list && list->type == ANGLEBRACKETLEFT &&
	list->next && list->next->next)
		return (cmd__removemiddle(list->next, 2));
	if (list->type == PIPELINE && lastpipe(list) &&
	lastpipe(list)->type >= 60 && lastpipe(list)->type != PIPELINE)
	{
		if (mainredir(v, lastpipe(list)->type, lastpipe(list)->next->line) == 0)
			return (0);
	}
	return (1);
}
