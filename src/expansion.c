/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 22:55:42 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/05 16:21:13 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_to_zero(size_t *i, size_t *j)
{
	*i = 0;
	*j = 0;
}

static void	parse_cmd(t_vars *v, t_exp *e)
{
	init_to_zero(&e->i, &e->j);
	while (e->array[e->array_iter][e->i] != '\0')
	{
		if (v->empty_quotes && (ft_counter(e->array[e->array_iter], "\"\'") != \
		ft_strlen(e->array[e->array_iter])))
			print_empty_token_space(v, e);
		if (e->array[e->array_iter][e->i] == '\\')
			copy_backslash(e);
		else if (e->array[e->array_iter][e->i] == '#' && e->i == 0)
			copy_hashtag(e);
		else if (e->array[e->array_iter][e->i] == '\'')
			copy_single_quote(v, e);
		else if (e->array[e->array_iter][e->i] == '\"')
			copy_double_quote(v, e);
		else if (e->array[e->array_iter][e->i] == '$' && \
			!ft_charsearch(e->array[e->array_iter][e->i + 1], ENV_DELIMS))
			copy_envvar(v, e);
		else if (e->array[e->array_iter][e->i] == ' ')
			copy_space(e);
		else
			copy_char(e);
		e->i += 1;
	}
}

static void	combine_strings(t_vars *v, t_exp *e)
{
	ft_bzero(e->sub_dst, PATH_MAX + 1);
	parse_cmd(v, e);
	if (ft_strlen(e->dst))
		ft_strlcat(e->dst, STRING_SPECIAL_CHAR, PATH_MAX + 1);
	ft_strlcat(e->dst, e->sub_dst, PATH_MAX + 1);
}

void		expansion(t_vars *v)
{
	t_exp e;

	ft_bzero(&e, sizeof(e));
	e.tmp = v->cmd;
	while (e.tmp)
	{
		e.array_size = 0;
		e.array = \
		ft_split_sep_exep(e.tmp->line, STRING_SPECIAL_CHAR2, &e.array_size);
		malloc_check(v, e.array);
		e.dst = ft_calloc(PATH_MAX + 1, sizeof(char));
		malloc_check(v, e.dst);
		e.array_iter = 0;
		while (e.array_iter < e.array_size)
		{
			combine_strings(v, &e);
			e.array_iter++;
		}
		ft_free_array((void **)e.array, e.array_size);
		ft_free(e.tmp->line);
		e.tmp->line = e.dst;
		e.tmp = e.tmp->next;
	}
	v->empty_quotes = 0;
}
