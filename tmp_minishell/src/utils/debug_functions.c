/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 21:10:17 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 16:55:11 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_vars *v, const char *title) //debug function
{
	t_list	*tmp;

	tmp = v->cmd;
	while (tmp)
	{
		printf("[%s][%s]\tat [%p] and [%p]\n", title, tmp->content, tmp->content, tmp);
		tmp = tmp->next;
	//	if (tmp)
	//		printf("\n");
	}
	//printf("\n");
}
