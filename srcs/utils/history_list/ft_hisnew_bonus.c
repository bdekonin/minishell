/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hisnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/23 19:56:20 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

t_history	*his__ft_lstnew(void *command, void *output, void *line)
{
	t_history *tmp;

	tmp = malloc(sizeof(t_history));
	if (!tmp)
		return (0);
	tmp->command = command;
	tmp->output = output;
	tmp->line = line;
	tmp->next = NULL;
	return (tmp);
}
