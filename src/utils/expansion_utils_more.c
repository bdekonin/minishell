/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils_more.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 15:34:27 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/05 09:22:50 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy_double_quote_empty(t_vars *v, t_exp *e)
{
	if (ft_counter(e->array[e->array_iter], "\"\'") == \
		ft_strlen(e->array[e->array_iter]))
		v->empty_quotes = 1;
	e->i += 1;
}

void		copy_double_quote(t_vars *v, t_exp *e)
{
	e->i += 1;
	copy_double_quote_empty(v, e);
	while (e->array[e->array_iter][e->i] != '\0' && \
			e->array[e->array_iter][e->i] != '\"')
	{
		if (e->array[e->array_iter][e->i] == '$' && \
			e->array[e->array_iter][(e->i) + 1] == '\"')
		{
			e->sub_dst[e->j] = e->array[e->array_iter][e->i];
			e->j += 1;
		}
		else if (e->array[e->array_iter][e->i] == '$')
			copy_envvar(v, e);
		else if (e->array[e->array_iter][e->i] == '\\' && \
			(e->array[e->array_iter][(e->i) + 1] == '\\' || \
			e->array[e->array_iter][(e->i) + 1] == '\"'))
			copy_backslash(e);
		else
		{
			e->sub_dst[e->j] = e->array[e->array_iter][e->i];
			e->j += 1;
		}
		e->i += 1;
	}
}

void		copy_single_quote(t_vars *v, t_exp *e)
{
	e->i += 1;
	if (ft_counter(e->array[e->array_iter], "\"\'") == \
	ft_strlen(e->array[e->array_iter]))
	{
		v->empty_quotes = 1;
		e->i += 1;
		return ;
	}
	while (e->array[e->array_iter][e->i] != '\0' && \
	e->array[e->array_iter][e->i] != '\'')
	{
		e->sub_dst[e->j] = e->array[e->array_iter][e->i];
		e->i += 1;
		e->j += 1;
	}
}

void		copy_space(t_exp *e)
{
	e->sub_dst[e->j] = CHAR_SPECIAL_CHAR;
	e->j += 1;
	while (e->array[e->array_iter][e->i] == ' ')
		e->i += 1;
}

void		copy_char(t_exp *e)
{
	e->sub_dst[e->j] = e->array[e->array_iter][e->i];
	e->j += 1;
}
