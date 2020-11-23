/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/23 21:35:08 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		find_env_name(t_env **head, char *name, char *content)
{
	t_env	*node;

	node = *head;
	while (node)
	{
		if (!ft_strncmp(node->name, name, ft_strlen(name) + 1))
		{
			free(name);
			free(node->content);
			node->content = content;
			return (1);
		}
		node = node->next;
	}
	return (0);
}

static int		check_valid_identifier(char *arg)
{
	size_t i;

	i = 0;
	if (arg[i] != '\0' && !ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	i++;
	while (arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]))
			i++;
		else if (arg[i] == '_')
			i++;
		else if (arg[i] == '=')
			return (1);
		else
			return (0);
	}
	return (1);
}

static int		add_new_env_vars(t_vars *v, char *arg)
{
	char	*ptr;
	char	*name;
	char	*content;
	size_t	len_identifier;

	if (!check_valid_identifier(arg))
	{
		ft_printf(INVALID_IDENTIFIER, "minishell", "export", arg);
		return (0);
	}
	len_identifier = ft_substrlen(arg, "=");
	name = ft_substr(arg, 0, len_identifier);
	malloc_check(v, name);
	ptr = ft_strchr(arg, '=');
	if (!ptr)
		content = NULL;
	else if (ptr && *ptr + 1 == '\0')
		content = ft_strdup("\0");
	else
		content = ft_strdup(ptr + 1);
	if (ptr && !content)
		ft_exit_error(v, EXIT_FAILURE, 1);
	if (!find_env_name(&v->env, name, content))
		create_new_env_var(v, name, content, 0);
	return (1);
}

int				ft_export(t_vars *v, char **params)
{
	size_t	i;

	if (!*params)
		return (export_declare_list(v));
	i = 0;
	while (params[i] != NULL)
	{
		if (!add_new_env_vars(v, params[i]))
			return (1);
		i++;
	}
	return (0);
}
