/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:32:07 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/23 16:28:40 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

int	his__ft_lstsize(t_history *lst)
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
