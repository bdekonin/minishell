/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_history.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 15:48:30 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/15 19:35:25 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** -c remove history
**
**
*/

static inline void		clear_history(t_history **head)
{
	his__ft_lstclear(head, free);
}

int						ft_history(t_vars *v, t_cmd *cmd, char **params)
{
	t_history	*temp;
	int			i;

	i = 0;
	temp = v->history_head;
	if (params[0] && !ft_strcmp("-c", params[0]))
		clear_history(&v->history_head);
	else
	{
		while (temp)
		{
			ft_printf("\t%d\t%s\n", i, temp->fullcommand);
			i++;
			temp = temp->next;
		}
		printf("\t%d\thistory\n", i);
	}
	if (!sethistory(&v->history_head, v->line, "his"))
		return (0);
	return (1);
}
