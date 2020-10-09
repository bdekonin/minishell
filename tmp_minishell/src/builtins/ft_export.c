/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/10/09 13:25:13 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		find_env_var_name(t_list **head, char *name, char *content)
{
	t_list	*tmp;
	t_env	*node;
	
	tmp = *head;
	while (tmp)
	{
		node = tmp->content;
		if (!ft_strncmp(node->name, name, ft_strlen(name) + 1))
		{
			ft_free(name);
			ft_free(node->content);
			node->content = content;
			return (1); //existing name found in env list
		}
		tmp = tmp->next;
	}
	return (0); //new name found in env list
}

static int		add_new_node_to_list(t_vars *v, char *name, char *content)
{
	t_list	*new;
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		ft_exit_error(v, EXIT_FAILURE);
	node->name = name;
	node->content = content;
	new = ft_lstnew(node);
	if (!new)
		ft_exit_error(v, EXIT_FAILURE);
	ft_lstadd_back(&v->env, new);
	return (1);
}

static int		check_valid_identifier(char *arg, char **name)
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
	
	if (!check_valid_identifier(arg, &name))
		ft_printf("%s: export: `%s': not a valid identifier\n", v->default_executable->content, arg);
		return (0);
	len_identifier = ft_substrlen(arg, "=");
	name = ft_substr(arg, 0, len_identifier);
	if (!name)
		ft_exit_error(v, EXIT_FAILURE);
	ptr = ft_strchr(arg, '=');
	if (!ptr)
		content = NULL;
	else if (ptr && ptr + 1 == '\0')
		content = ft_strdup("\0");
	else
		content = ft_strdup(ptr + 1);
	if (ptr && !content)
		ft_exit_error(v, EXIT_FAILURE);
	if (!find_env_var_name(&v->env, name, content) && !add_new_node_to_list(v, name, content))
		return (0); //return or exit????
	return (1);
	// if (ptr)
	// 	*ptr = '\0';
	// name = ft_strdup(arg);
	// if (!name)
	// 	ft_exit_error(v, EXIT_FAILURE);
	// if (!ptr)
	// 	content = NULL;
	// else if (ptr && ptr + 1 == '\0')
	// 	content = ft_strdup("\0");
	// else
	// 	content = ft_strdup(ptr + 1);
	// if (ptr && !content)
	// {
	// 	ft_free (name);
	// 	ft_exit_error(v, EXIT_FAILURE);
	// }
	// if (!find_env_var_name(&v->env, name, content) && !add_new_node_to_list(v, name, content))
	// 	return (0);
	// return (1);
}

int 			ft_export(t_vars *v, char **params)
{
	size_t	i;

	if (!params[0])
	{
		if (!export_declare_list(v))
			return (0);
		return (1);
	}
	i = 0;
	while (params[i] != NULL)
	{
		if (!add_new_env_vars(v, params[i]))
			return (0);
		i++;
	}
//	if (!sethistory(&v->history_head, v->line, "0"))
//		return (0);
	return (1);
}
