/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmdsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:32:07 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/11 16:52:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	cmd__ft_lstsize(t_cmd *lst)
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
