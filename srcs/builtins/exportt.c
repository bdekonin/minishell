/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exportt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/24 13:29:52 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"


/*
** TODO lars
**
**
**
**
**         \#      Replace with a `#' character.  This would be useful when
**                 you need a `#' as the first character in one of the argu-
**                 ments created by splitting apart the given string.
**         \$      Replace with a `$' character.
**         \_      If this is found inside of a double-quoted string, then
**                 replace it with a single blank.  If this is found outside
**                 of a quoted string, then treat this as the separator char-
**                 acter between new arguments in the original string.
**         \"      Replace with a <double quote> character.
**         \'      Replace with a <single quote> character.
**         \\      Replace with a backslash character.
**
*/

// static int	find_env_var_name(t_env **head, char *name, char *content)
// {
// 	t_env	*tmp;
	
// 	tmp = *head;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
// 		{
// 			free(name);
// 			free(tmp->content);
// 			tmp->content = content;
// 			return (1); //existing name found in env list
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0); //new name found in env list
// }

static int	do_dollar(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	size_t env_len;
	char *env_name;
	char *env_content;

	*i += 1;
	env_len = 0;
	while (src[*i + env_len] != '\0' && src[*i + env_len] != '\"' && src[*i + env_len] != ' ' && src[*i + env_len] != '\\' && src[*i + env_len] != '$' && src[*i + env_len] != '/')
		env_len++;
	if (env_len == 0)
		return (0); //env var name has len of 0. Don't delete this check.
	env_name = src + *i;
	env_content = find_environment_variable(v, env_name, &env_len);
	if (!env_content)
		return (0); //env name not in env list
	// maybe expand dst here?
	ft_strlcat(dst + *j, env_content, ft_strlen(dst) + 1);
	*i += env_len - 1;
	*j += ft_strlen(env_content);
	return (1);
}

static int	do_double_quote(t_vars *v, char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	while (src[*i] != '\0' && src[*i] != '\"')
	{
		if (src[*i] == '$')
		{
			do_dollar(v, dst, src, i, j); //check return
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

static int	do_single_quote(char *dst, char *src, size_t *i, size_t *j)
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

static int	do_hashtag(char *src, size_t *i)
{
	*i += 1;
	while (src[*i] != '\0')
		*i += 1;
	return (1);
}

static int	do_backslash(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	dst[*j] = src[*i];
	*j += 1;
	return (1);
}

static int parse_input(t_vars *v, char *dst, char *src)
{
	int ret;
	size_t i; //index in src
	size_t j; //index in dst

	ret = 1;
	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '\\')
			ret = do_backslash(dst, src, &i, &j);
		else if (src[i] == '#' && i == 0)
			ret = do_hashtag(src, &i);
		else if (src[i] == '\'')
			ret = do_single_quote(dst, src, &i, &j);
		else if (src[i] == '\"')
			ret = do_double_quote(v, dst, src, &i, &j);
		else if (src[i] == '$')
			ret = do_dollar(v, dst, src, &i, &j);
		else
		{
			dst[j] = src[i];
			j++;
		}
		if (ret != 1)
			return (ret);
		i++;
	}
	return (1);
}

static size_t check_declare_option(char *first_param)
{
	if (!ft_strncmp(first_param, "declare", 8))
		return (1);
	return (0);
}

static size_t get_size_params(char **params)
{
	size_t size;

	size = 0;
	while (params[size])
		size++;
	return (size);
}

int 			exportt(t_vars *v, t_cmd *cmd, char **params) //tttttt?
{
	size_t	i;
	size_t	d;
	size_t	size;
	int 	ret;
	char	**dst;
	
	size = get_size_params(params);
	if (size == 0)
	{
		printf("alleen export dus\n");
		return (0); //return (export_declare_-x_list);
	}
	dst = ft_calloc(size + 1, sizeof(char *));
	if (!dst)
		return (0); //malloc
	i = 0;
	d = check_declare_option(params[0]);
	while (i + d < size)
	{
		dst[i] = ft_calloc(ft_strlen(params[i + d] + 1), sizeof(char));
		if (!dst[i])
		{
			ft_free_array((void **)dst, i);
			return (0); //malloc
		}
		ret = parse_input(v, dst[i], params[i + d]);
		if (ret == 0)
			return (0); //some error happened, like malloc
		i++;
	}
	if (!sethistory(&v->history_head, v->line, "0"))
		return (0);
	(void)(cmd);
	return (1);
}



		// if (!find_env_var_name(&v->env_head, array[i], array[i + 1]))
		// {
		// 	env__ft_lstadd_back(&v->env_head, env__ft_lstnew(array[i], array[i + 1]));
		// 	env__ft_lstmove_back("_", v->env_head);	
		// }