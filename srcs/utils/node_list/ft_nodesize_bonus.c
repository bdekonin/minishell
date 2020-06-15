/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hissize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:32:07 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 18:01:08 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

int	node__ft_lstsize(t_node *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
