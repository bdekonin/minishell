/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nodenew_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/05 10:49:56 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

t_cmd		*cmd__ft_lstnew(unsigned char type, char *line)
{
	t_cmd *tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (0);
	tmp->type = type;
	tmp->line = line;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}
