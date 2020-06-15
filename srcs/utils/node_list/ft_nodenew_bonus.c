/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nodenew_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/15 16:20:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

t_node		*node__ft_lstnew(unsigned char type, int i, void *line)
{
	t_node *tmp;

	tmp = malloc(sizeof(t_node));
	if (!tmp)
		return (0);
	tmp->type = type;
	tmp->i = i;
	tmp->line = line;
	tmp->next = NULL;
	return (tmp);
}
