/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sethistory.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 14:10:25 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/08 14:31:37 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int		sethistory(t_history **his, char *fullcommand, char *ret, \
															char *singlecommand)
{
	t_history		*newlist;
	char			*tmp;
	char			*tmp2;

	tmp = ft_strdup(fullcommand);
	if (!tmp)
		return (0);
	tmp2 = ft_strdup(singlecommand);
	if (!tmp2)
	{
		free(tmp);
		return (0);
	}
	ft_printf("\x1B[31m%s - %s - %s\n\x1B[0m", fullcommand, ret, singlecommand);
	if (!*his)
	{
		*his = his__ft_lstnew(tmp, ret, tmp2);
		if (!*his)
		{
			free(tmp);
			free(tmp2);
			return (0);
		}
		else
			return (1);
	}
	else
	{
		newlist = his__ft_lstnew(tmp, ret, tmp2);
		if (!newlist)
		{
			free(tmp);
			free(tmp2);
			return (0);
		}
		his__ft_lstadd_front(&*his, newlist);
	}
	return (1);
}
