/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exportt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/25 12:33:50 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"


static char		**free_array(char **array, size_t i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
	return (NULL);
}

static size_t	get_size_of_src(char **src)
{
	size_t i;

	if (!src)
		return (0);
	i = 0;
	while (src[i] != NULL)
		i++;
	return (i);
}

char			**ft_realloc(char **src, char *line)
{
	size_t	size;
	char	**dst;
	size_t	i;

	size = get_size_of_src(src);
	dst = ft_calloc(size + 2, sizeof(char *));
	if (!dst)
		return (free_array(src, size));
	i = 0;
	while (i < size)
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	free_array(src, size);
	dst[i] = ft_strdup(line);
	if (!dst[i])
		return (free_array(dst, i));
	src = dst;
	return (dst);
}



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

static int	find_env_var_name(t_env **head, char *name, char *content)
{
	t_env	*tmp;
	
	tmp = *head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
			free(name);
			free(tmp->content);
			tmp->content = content;
			return (1); //existing name found in env list
		}
		tmp = tmp->next;
	}
	return (0); //new name found in env list
}

static int	copy_double_quote(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	while (src[*i] != '\0' && src[*i] != '\"')
	{
		dst[*j] = src[*i];
		*i += 1;
		*j += 1;
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

static int	copy_backslash(char *dst, char *src, size_t *i, size_t *j)
{
	*i += 1;
	dst[*j] = src[*i];
	*j += 1;
	return (1);
}

static int parse_input(char *dst, char *src)
{
	size_t i; //index in src
	size_t j; //index in dst

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '\\')
			copy_backslash(dst, src, &i, &j);
		else if (src[i] == '\'')
			copy_single_quote(dst, src, &i, &j);
		else if (src[i] == '\"')
			copy_double_quote(dst, src, &i, &j);
		else if (src[i] == '#' && i == 0)
			return (1);
		else
		{
			dst[j] = src[i];
			j++;
		}
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
	while (params[size] != NULL)
		size++;
	return (size);
}

static int	add_new_env_vars(t_vars *v, char **dst)
{
	size_t i;
	char *ptr;
	char *name;
	char *cont;

	i = 1; // 0 = export
	while (dst[i] != NULL)
	{
		ptr = ft_strchr(dst[i], '=');
		*ptr = '\0';
		name = dst[i];
		if (!ptr)
			return (0); //malloc
		cont = ft_strdup(ptr + 1);
		if (!cont)
		{
			free (name);
			return (0); //malloc
		}
		if (!find_env_var_name(&v->env_head, name, cont))
		{
			env__ft_lstadd_back(&v->env_head, env__ft_lstnew(name, cont));
			env__ft_lstmove_back("_", v->env_head);	
		}
		i++;
	}
	return (1);
}

int 			exportt(t_vars *v, t_cmd *cmd, char **params)
{
	size_t	i;
	size_t	d;
	size_t	size;
	char	**dst;
	
	size = get_size_params(params);
	if (size == 0)
	{
		printf("alleen export dus\n");
		return (0); //return (export_declare_-x_list);
	}
	i = 0;
	dst = 0;
	d = check_declare_option(params[0]);
	while (i + d < size)
	{
		dst = ft_realloc(dst, params[i + d]);
		if (!dst)
			return (0);
		parse_input(dst[i], params[i + d]);
		i++;
	}
	add_new_env_vars(v, dst);
	ft_free_array((void **)dst, i);
	if (!sethistory(&v->history_head, v->line, "0"))
		return (0);
	(void)(cmd);
	return (1);
}
