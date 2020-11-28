/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 12:03:38 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/28 13:36:19 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ret_value_last_cmd(t_vars *v, char *dst, size_t *i, size_t *j)
{
	char *tmp;

	tmp = ft_itoa(v->cmd_ret);
	malloc_check(v, tmp);
	ft_strlcat(dst + *j, tmp, PATH_MAX + 1);
	*j += ft_strlen(tmp);
	*i += 1;
	ft_free(tmp);
	return (1);
}

static int	env_var_with_len_zero(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	if (src[*i] == '\"')
	{
		copy_double_quote(v, dst, src, i, j);
		return (1);
	}
	dst[*j] = '$';
	*j += 1;
	return (1);
}

static int	empty_env_content(size_t env_len, size_t *i)
{
	*i += env_len + 0;
	return (1);
}

int			copy_envvar(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	size_t		env_len;
	char		*env_name;
	t_env		*env_content;
	char		*split_content;

	*i += 1;
	if (src[*i] == '?')
		return (ret_value_last_cmd(v, dst, i, j));
	if (ft_isdigit(src[*i]))
		return (0);
	else
		env_len = find_identifier_len(src + *i);
//	printf("env_len = [%lu]\n", env_len);
	if (env_len == 0)
		return (env_var_with_len_zero(v, dst, src, i, j));
	env_name = ft_substr(src, *i, env_len);
//	printf("env_name = [%s]\n", env_name);
	env_content = find_env(v, env_name, &env_len);
//	printf("env_content = [%s]\n", env_content->content);
	ft_free(env_name);
	if (!env_content)
		return (empty_env_content(env_len, i));
	split_content = ft_reduce_spaces(env_content->content, 0, 0);
	malloc_check(v, split_content);
	ft_strlcat(dst + *j, split_content, PATH_MAX + 1);
	*j += ft_strlen(split_content);
	*i += env_len - 1;
	ft_free(split_content);
	return (1);
}
