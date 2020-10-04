/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/09/14 16:08:18 by lverdoes      ########   odam.nl         */
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
			free(name);
			free(node->content);
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
		return (0);
	node->name = name;
	node->content = content;
	new = ft_lstnew(node);
	ft_lstadd_back(&v->env, new);
//	env__ft_lstmove_back("_", v->env); 		//waarom dit?	
	return (1);
}

static int		add_new_env_vars(t_vars *v, char *dst)
{
	char	*ptr;
	char	*name;
	char	*content;

	ptr = ft_strchr(dst, '=');
	if (ptr)
		*ptr = '\0';
	name = ft_strdup(dst);
	if (!name)
		return (0);
	if (!ptr)
		content = NULL;
	else if (ptr && ptr + 1 == '\0')
		content = ft_strdup("\0");
	else
		content = ft_strdup(ptr + 1);
	if (ptr && !content)
	{
		free (name);
		return (0);
	}
	if (!find_env_var_name(&v->env, name, content) && !add_new_node_to_list(v, name, content))
		return (0);
	return (1);
}

int 			ft_export(t_vars *v, char **params)
{
	size_t	i;

	if (!params[0])
	{
		//if (!export_declare_list(&v->env_head))
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
