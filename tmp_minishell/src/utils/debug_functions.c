/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 21:10:17 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/12 20:13:11 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_vars *v, const char *title) //debug function
{
	t_list	*tmp;

	tmp = NULL;
	while (tmp)
	{
		printf("[%s][%s]\n", title, tmp->content);
		tmp = tmp->next;
	//	if (tmp)
	//		printf("\n");
	}
	//printf("\n");
}
