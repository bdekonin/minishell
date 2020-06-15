/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 21:06:45 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

t_node	*node__ft_lstnew(void *type, void *size, void **argv)
{
	t_node *tmp;

	tmp = malloc(sizeof(t_node));
	if (!tmp)
		return (0);
	tmp->type = type;
	tmp->size = size;
	tmp->argv = argv;
	tmp->next = NULL;
	return (tmp);
}
