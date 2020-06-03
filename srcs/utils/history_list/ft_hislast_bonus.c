/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:38:32 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/23 16:26:55 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

t_history	*his__ft_lstlast(t_history *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
