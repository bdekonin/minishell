/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 21:10:17 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 13:01:04 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_vars *v) //debug function
{
	t_list	*tmp;

	tmp = v->cmd;
	while (tmp)
	{
		printf("[%s]\tat [%p] and [%p]\n", tmp->content, tmp->content, tmp);
		tmp = tmp->next;
	//	if (tmp)
	//		printf("\n");
	}
	//printf("\n");
}
