/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argumentremover.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 22:27:02 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/01 11:42:39 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int argumentremover(t_vars *v, t_list *list)
{
	t_list *currcommand;
	t_list *nextcommand;
	
	if (list->next && !is_redirection(list->next->content))
		return (0);
	if (list->next == NULL || list->next->next == NULL)
		return (0);
	if (firstpipe(list) == NULL)
		return (0);
	if (ft_strncmp(list->next->content, "<", 1))
		return (0);
	currcommand = list;
	nextcommand = list->next->next->next;

	// dprintf(2, "currcommand = [%s]\n", currcommand->content);
	// dprintf(2, "nextcommand = [%s]\n", nextcommand->content);
	
	ft_lst_remove_one(&v->cmd, list->next->next);
	ft_lst_remove_one(&v->cmd, list->next);
	
	

	// while (list)
	// {
	// 	dprintf(2, "lst = [%s]\n", list->content);
	// 	list = list->next;
	// }
	return (1);
}