/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 22:55:42 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/13 18:56:02 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_double_quote(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
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

static void	copy_single_quote(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
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

static void parse_cmd(t_vars *v, char *dst, char *src)
{
	size_t i;
	size_t j;
	
	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '\\')
			copy_backslash(dst, src, &i, &j);
		else if (src[i] == '#' && i == 0)
			copy_hashtag(src, &i);
		else if (src[i] == '\'')
			copy_single_quote(dst, src, &i, &j);
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
			i--;
		}
		else
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
}

void		expansion(t_vars *v)
{
	char	*dst;
	t_cmd	*tmp;
	char	**src;

	tmp = v->cmd;
	while (tmp)
	{
		src = &tmp->line;
	//	printf("before exp = [%s]\n", *src);			//debug
		dst = ft_calloc(PATH_MAX + 1, sizeof(char));
		if (!dst)
			ft_exit_error(v, EXIT_FAILURE, 1);
		parse_cmd(v, dst, *src);
		ft_free(*src);
		*src = dst;
	//	printf("after  exp = [%s]\n", *src);			//debug
		tmp = tmp->next;
	}
}
