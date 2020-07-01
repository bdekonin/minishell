/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nodenew_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/01 14:12:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

t_node		*node__ft_lstnew(t_cmd **cmd)
{
	t_node *tmp;

	tmp = malloc(sizeof(t_node));
	if (!tmp)
		return (0);
	tmp->cmd = *cmd;
	tmp->next = NULL;
	return (tmp);
}

t_cmd		*cmd__ft_lstnew(unsigned char type, char *line)
{
	t_cmd *tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (0);
	tmp->type = type;
	tmp->line = line;
	tmp->next = NULL;
	return (tmp);
}

