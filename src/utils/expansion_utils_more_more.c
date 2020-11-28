/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils_more_more.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 15:37:50 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/28 15:38:26 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_hashtag(t_exp *e)
{
	e->i += 1;
	while (e->array[e->array_iter][e->i] != '\0')
		e->i += 1;
}

void	copy_backslash(t_exp *e)
{
	e->i += 1;
	e->sub_dst[e->j] = e->array[e->array_iter][e->i];
	e->j += 1;
}

void	print_empty_token_space(t_vars *v, t_exp *e)
{
	e->sub_dst[e->j] = ' ';
	e->j += 1;
	v->empty_quotes = 0;
}
