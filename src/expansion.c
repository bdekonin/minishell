/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 22:55:42 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/16 15:22:11 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_double_quote(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	if (ft_counter(src, "\"\'") == ft_strlen(src))
	{
		v->empty_quotes = 1;
		*i += 1;
		return ;
	}
	while (src[*i] != '\0' && src[*i] != '\"')
	{
		if (src[*i] == '$')
		{
			copy_envvar(v, dst, src, i, j);
			*i += 1;
		}
		else
		{
			dst[*j] = src[*i];
			*i += 1;
			*j += 1;
		}
	}
}

static void	copy_single_quote(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	if (ft_counter(src, "\"\'") == ft_strlen(src))
	{
		v->empty_quotes = 1;
		*i += 1;
		return ;
	}
	while (src[*i] != '\0' && src[*i] != '\'')
	{
		dst[*j] = src[*i];
		*i += 1;
		*j += 1;
	}
}

static void	copy_hashtag(char *src, size_t *i)
{
	*i += 1;
	while (src[*i] != '\0')
		*i += 1;
}

static void copy_backslash(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	dst[*j] = src[*i];
	*j += 1;
}

static void	print_empty_token_space(t_vars *v, char *dst, size_t *j)
{
	dst[*j] = ' ';
	*j += 1;
	v->empty_quotes = 0;
}

static void parse_cmd(t_vars *v, char *dst, char *src)
{
	size_t i;
	size_t j;
	
	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (v->empty_quotes && (ft_counter(src, "\"\'") != ft_strlen(src)))
			print_empty_token_space(v, dst, &j);
		if (src[i] == '\\')
			copy_backslash(dst, src, &i, &j);
		else if (src[i] == '#' && i == 0)
			copy_hashtag(src, &i);
		else if (src[i] == '\'')
			copy_single_quote(v, dst, src, &i, &j);
		else if (src[i] == '\"')
			copy_double_quote(v, dst, src, &i, &j);
		else if (src[i] == '$')
			copy_envvar(v, dst, src, &i, &j);
		else if (src[i] == ' ')
		{
			dst[j] = '*';
			j++;
			while (src[i] == ' ')
				i++;
		}
		else
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
}

static void	combine_strings(t_vars *v, char *dst, char **src, size_t i)
{
	char sub_dst[PATH_MAX + 1];
	
//	printf("src = [%s]\n", src[i]);
	ft_bzero(sub_dst, PATH_MAX + 1);
	parse_cmd(v, sub_dst, src[i]);
//	printf("dst = [%s]\n", sub_dst);
	if (ft_strlen(dst))
		ft_strlcat(dst, "*", PATH_MAX + 1);
	ft_strlcat(dst, sub_dst, PATH_MAX + 1);
}

void		expansion(t_vars *v)
{
	char	*dst;
	t_cmd	*tmp;
	char	**array;
	size_t	i;
	size_t	array_size;

	tmp = v->cmd;
	while (tmp)
	{
//		printf("before exp = [%s]\n", tmp->line);			//debug
		array_size = 0;
		array = ft_split_sep_exep(tmp->line, "* ", &array_size);
		malloc_check(v, array);
		dst = ft_calloc(PATH_MAX + 1, sizeof(char));
		malloc_check(v, dst);
		i = 0;
		while (i < array_size)
		{
			combine_strings(v, dst, array, i);
			i++;
		}
		ft_free_array((void **)array, array_size);
		ft_free(tmp->line);
		tmp->line = dst;
//		printf("after  exp = [%s]\n", tmp->line);			//debug
		tmp = tmp->next;
	}
}
