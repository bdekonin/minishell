/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 12:03:38 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/28 14:37:54 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ret_value_last_cmd(t_vars *v, t_exp *e)
{
	char *tmp;

	tmp = ft_itoa(v->cmd_ret);
	malloc_check(v, tmp);
	ft_strlcat(e->sub_dst + e->j, tmp, PATH_MAX + 1);
	e->j += ft_strlen(tmp);
	e->i += 1;
	ft_free(tmp);
	return (1);
}

static int	env_var_with_len_zero(t_vars *v, t_exp *e)
{
	if (e->array[e->array_iter][e->i] == '\"')
	{
		copy_double_quote(v, e);
		return (1);
	}
	e->sub_dst[e->j] = '$';
	e->j += 1;
	return (1);
}

static int	empty_env_content(size_t env_len, size_t *i)
{
	*i += env_len + 0;
	return (1);
}

int			copy_envvar(t_vars *v, t_exp *e)
{
	size_t	env_len;
	char	*env_name;
	t_env	*env_content;
	char	*split_content;

	e->i += 1;
	if (e->array[e->array_iter][e->i] == '?')
		return (ret_value_last_cmd(v, e));
	if (ft_isdigit(e->array[e->array_iter][e->i]))
		return (0);
	env_len = find_identifier_len(e->array[e->array_iter] + e->i);
	if (env_len == 0)
		return (env_var_with_len_zero(v, e));
	env_name = ft_substr(e->array[e->array_iter], e->i, env_len);
	env_content = find_env(v, env_name, &env_len);
	ft_free(env_name);
	if (!env_content)
		return (empty_env_content(env_len, &e->i));
	split_content = ft_reduce_spaces(env_content->content);
	malloc_check(v, split_content);
	ft_strlcat(e->sub_dst + e->j, split_content, PATH_MAX + 1);
	e->j += ft_strlen(split_content);
	e->i += env_len - 1;
	ft_free(split_content);
	return (1);
}
