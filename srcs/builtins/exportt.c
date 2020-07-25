/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exportt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/25 21:04:06 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int		find_env_var_name(t_env **head, char *name, char *content)
{
	t_env	*tmp;
	size_t	len;
	
	tmp = *head;
	while (tmp)
	{
		len = ft_strlen(tmp->name);
		if (ft_strlen(name) > len)
			len = ft_strlen(name);
		if (!ft_strncmp(tmp->name, name, len))
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
		return (0); //malloc
	if (!ptr)
		content = ft_strdup("\0");
	else
		content = ft_strdup(ptr + 1);
	if (!content)
	{
		free (name);
		return (0); //malloc
	}
	//printf("n = [%s]\n", name); //debug
	//printf("c = [%s]\n", content); //debug
	if (!find_env_var_name(&v->env_head, name, content))
	{
		env__ft_lstadd_back(&v->env_head, env__ft_lstnew(name, content));
		env__ft_lstmove_back("_", v->env_head);	
	}
	return (1);
}

static void		swap(char **s1, char **s2)
{
	char *tmp;
	
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void		ascii_sort(char **array)
{
	size_t len;
	size_t i;
	size_t j;

	len = 0;
	while (array[len] != NULL)
		len++;
	len--;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			if (ft_strncmp(array[j], array[j + 1], ft_strlen(array[j])) > 0)
				swap(&array[j], &array[j + 1]);
			j++;
		}
		i++;
	}
}

static int		print_declare_list(char **array)
{
	size_t i;

	ascii_sort(array);
	i = 0;
	while (array[i] != NULL)
	{
		write(1, array[i], ft_strlen(array[i]));
		write(1, "\n", 1);
		i++;	
	}
	ft_free_array((void **)array, i);
	return (1);
}

static int		declare_list(t_env **head)
{
	t_env	*tmp;
	size_t i;
	size_t len;
	char	**array;
	
	len = 0;
	tmp = *head;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	array = ft_calloc(len + 1, sizeof(char *));
	if (!array)
		return (0);
	tmp = *head;
	i = 0;
	while (i < len && tmp)
	{
		if (*(tmp->content) == '\0')
			array[i] = ft_strxjoin("declare -x ", tmp->name, NULL);
		else
			array[i] = ft_strxjoin("declare -x ", tmp->name, "=\"", tmp->content, "\"", NULL);
		if (!array[i])
		{
			ft_free_array((void **)array, i);
			return (0);
		}
		i++;
		tmp = tmp->next;
	}
	return (print_declare_list(array));
}

int 			exportt(t_vars *v, t_cmd *cmd, char **params)
{
	size_t	i;

	if (!params[0])
	{
		if (!declare_list(&v->env_head))
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
