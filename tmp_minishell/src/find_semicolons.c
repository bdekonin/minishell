/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_semicolons.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 22:27:40 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/12 13:47:05 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_semicolons(t_list *tmp)
{
	size_t	counter;

	counter = 1;
	while (tmp)
	{
		if (is_semicolon(tmp->content))
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}

void			find_semicolons(t_vars *v)
{
	size_t	counter;
	size_t	i;
	t_list	*tmp;

	counter = count_semicolons(v->cmd);
//	printf("[%lu]\n", counter); 				//debug
	v->semicolon_ptrs = ft_calloc(counter + 1, sizeof(t_list *));
	if (!v->semicolon_ptrs)
		ft_exit_error(v, EXIT_FAILURE);
	tmp = v->cmd;
	v->semicolon_ptrs[0] = v->cmd;
	i = 1;
	while (tmp && i < counter)
	{
		if (is_semicolon(tmp->content))
		{
			v->semicolon_ptrs[i] = tmp->next;
			i++;
		}	
		tmp = tmp->next;
	}
}
