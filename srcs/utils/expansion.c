/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 22:55:42 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/08/04 11:54:12 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static size_t	ft_substrlen(const char *str, const char *set)
{
	size_t i;
	size_t j;
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (str[i] == set[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

// static char		*ft_strexp(char *src1, char *src2, char *tar, size_t tar_len)
// {
// 	size_t len;
// 	char *dst;
// 	if (!src1 || tar < src1 || tar_len > ft_strlen(src1))
// 		return (NULL);
// 	len = ft_strlen(src1) - tar_len + ft_strlen(src2);
// 	dst = ft_calloc(len + 1, sizeof(char));
// 	if (!dst)
// 		return (NULL);
// 	ft_strlcpy(dst, src1, tar - src1 + 1); 
// 	ft_strlcat(dst, src2, len + 1);
// 	ft_strlcat(dst, tar + tar_len, len + 1);
// 	return (dst);
// }

static int	copy_envvar(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	size_t env_len;
	char *env_name;
	char *env_content;
	*i += 1;
	env_len = ft_substrlen(src + *i, "\"\\ $/");
	if (env_len == 0)
		return (0); //env var name has len of 0. Don't delete this check.
	env_name = src + *i;
	env_content = find_environment_variable(v, env_name, &env_len);
	if (!env_content)
		return (0); //env name not in env list
	ft_strlcat(dst + *j, env_content, PATH_MAX + 1);
	*i += env_len - 1;
	*j += ft_strlen(env_content);
	return (1);
}

static int	copy_double_quote(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	while (src[*i] != '\0' && src[*i] != '\"')
	{
		if (src[*i] == '$')
		{
			copy_envvar(v, dst, src, i, j); //check return
			*i += 1;
		}
		else
		{
			dst[*j] = src[*i];
			*i += 1;
			*j += 1;
		}
	}
	return (1);
}

static int	copy_single_quote(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	while (src[*i] != '\0' && src[*i] != '\'')
	{
		dst[*j] = src[*i];
		*i += 1;
		*j += 1;
	}
	return (1);
}

static int	copy_hashtag(char *src, size_t *i)
{
	*i += 1;
	while (src[*i] != '\0')
		*i += 1;
	return (1);
}

static int copy_backslash(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	dst[*j] = src[*i];
	*j += 1;
	return (1);
}

static int parse_cmd(t_vars *v, char *dst, char *src)
{
	size_t i;
	size_t j;
	i = 0;
	j = 0;
	while (src[i] != '\0') // && dst[j] != '\0';
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
	return (1);
}

int		expansions(t_vars *v, char **arg)
{
	char *dst;
	//dst = ft_calloc(ft_strlen(*arg) + 1, sizeof(char));
	dst = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!dst)
		return (0);
	if (!parse_cmd(v, dst, *arg))
	{
		free(dst);
		return (0);
	}
	free(*arg);
	*arg = dst;
	return (1);
}
