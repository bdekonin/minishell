/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/10 10:42:36 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

t_history	*his__ft_lstnew(void *fullcommand, void *ret)
{
	t_history *tmp;

	tmp = malloc(sizeof(t_history));
	if (!tmp)
		return (0);
	tmp->fullcommand = fullcommand;
	tmp->ret = ret;
	tmp->next = NULL;
	return (tmp);
}
