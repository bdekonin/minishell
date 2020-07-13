/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sethistory.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 14:10:25 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/13 18:06:36 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int		sethistory(t_history **his, char *fullcommand, char *ret_str)
{
	t_history		*newlist;
	char			*tmp;
	char			*ret;

	tmp = ft_strdup(fullcommand);
	if (!tmp)
		return (0);
	ret = ft_strdup(ret_str);
	if (!ret)
	{
		free(tmp);
		return (0);
	}
	if (!*his)
	{
		*his = his__ft_lstnew(tmp, ret);
		if (!*his)
		{
			free(tmp);
			return (0);
		}
		return (1);
	}
	newlist = his__ft_lstnew(tmp, ret);
	if (!newlist)
	{
		free(tmp);
		return (0);
	}
	his__ft_lstadd_front(&*his, newlist);
	ret = NULL;
	return (1);
}
