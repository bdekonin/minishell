/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 22:55:42 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/07 14:06:12 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_envvar(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	size_t env_len;
	char *env_name;
	char *env_content;
	char *tmp;
	
	*i += 1;
	if (src[*i] == '?')			//new func
	{
		tmp = ft_itoa(v->cmd_ret);
		if (!tmp)
			return (0);
		ft_strlcat(dst + *j, tmp, PATH_MAX + 1);
		free(tmp);
		return (1);
	}
	env_len = ft_substrlen(src + *i, "\"\\ =$/");		 //protect
	//printf("env_len=[%lu]\n", env_len); //debug
	if (env_len == 0)
	{
		dst[*j] = '$';
		*j += 1;
		*i -= 1;
		return (1); //env var name has len of 0. Don't delete this check.
	}
	env_name = src + *i;
	env_name = ft_substr(src + *i, 0, env_len);
	if (!env_name)
		return (0);
	env_content = find_environment_variable(v, env_name, &env_len);
	//printf("env_name=[%s]\n", env_name); //debug
	//printf("env_content=[%s]\n", env_content); //debug
	if (!env_content)
	{
		*i += env_len - 1;
		return (1);
	}	
	ft_strlcat(dst + *j, env_content, PATH_MAX + 1);
	*j += ft_strlen(env_content);
	*i += env_len -1;
	return (1);
	
}

static int	copy_double_quote(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	int ret;
	
	*i += 1;
	while (src[*i] != '\0' && src[*i] != '\"')
	{
		if (src[*i] == '$')
		{
			ret = copy_envvar(v, dst, src, i, j); //check return
			if (!ret)
				return (0);
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
	int ret;
	size_t i;
	size_t j;
	
	i = 0;
	j = 0;
	ret = 1;
	while (src[i] != '\0') // && dst[j] != '\0';
	{
		if (src[i] == '\\')
			copy_backslash(dst, src, &i, &j);
		else if (src[i] == '#' && i == 0)
			copy_hashtag(src, &i);
		else if (src[i] == '\'')
			copy_single_quote(dst, src, &i, &j);
		else if (src[i] == '\"')
			ret = copy_double_quote(v, dst, src, &i, &j);
		else if (src[i] == '$')
			ret = copy_envvar(v, dst, src, &i, &j);
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
		if (!ret)
			return (0);
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
		return (ft_free(dst));
	ft_free(*arg);
	*arg = dst;
	return (1);
}
