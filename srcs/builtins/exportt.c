/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exportt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/08/05 09:54:14 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int		find_env_var_name(t_env **head, char *name, char *content)
{
	t_env	*tmp;
	
	tmp = *head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
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
	if (!find_env_var_name(&v->env_head, name, content))
	{
		env__ft_lstadd_back(&v->env_head, env__ft_lstnew(name, content));
		env__ft_lstmove_back("_", v->env_head);	
	}
	return (1);
}

int 			exportt(t_vars *v, t_cmd *cmd, char **params)
{
	size_t	i;

	if (!params[0])
	{
		if (!export_declare_list(&v->env_head))
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
	if (!sethistory(&v->history_head, v->line, "0"))
		return (0);
	(void)(cmd);
	return (1);
}
