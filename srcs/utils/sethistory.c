/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sethistory.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 14:10:25 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/02 14:13:06 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int		sethistory(t_history **his, char *fullcommand, char *ret, \
															char *singlecommand)
{
	t_history		*newlist;
	char			*tmp;
	char			*tmp2;

	tmp = ft_strdup(singlecommand);
	tmp2 = ft_strdup(fullcommand);
	if (!tmp || !tmp2)
		return (0);
	if (!*his)
	{
		*his = his__ft_lstnew(tmp, ret, tmp2);
		if (!*his)
			return (0);
		else
			return (1);
	}
	else
	{
		newlist = his__ft_lstnew(tmp, ret, tmp2);
		if (!newlist)
			return (0);
		his__ft_lstadd_front(&*his, newlist);
	}
	return (1);
}
