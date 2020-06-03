/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/21 16:34:41 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static size_t	count_vars(char **params)
{
	size_t i;

	i = 0;
	while (params[i] && ft_strncmp(params[i], ";", 3))
	{
		i++;
	}
	return (i);
}

static int	trim_strings(char **s1, char **s2, char **src)
{
	char set[3];

	set[0] = 34;
	set[1] = 39;
	set[2] = 0;
	*s1 = ft_strtrim(src[0], set);
	if (!*s1)
	{
		ft_free_array((void*)src, 2);
		return (0);
	}
	*s2 = ft_strtrim(src[1], set);
	if (!*s2)
	{
		free(*s1);
		ft_free_array((void*)src, 2);
		return (0);
	}
	ft_free_array((void*)src, 2);
	return (1);
}

static int	find_env_var_name(t_env **head, char **name, char **content)
{
	t_env	*tmp;
	
	tmp = *head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, *name, ft_strlen(*name)))
		{
			free(*name);
			free(tmp->content);
			tmp->content = *content;
			return (1); //existing name found in env list
		}
		tmp = tmp->next;
	}
	return (0); //new name found in env list
}

int 			export(t_vars *v, char **params)
{
	char	**array;
	size_t	size;
	size_t	i;
	char	*dst_name;
	char	*dst_content;
	int test;
	// printf("params [1]%s", params[0]);

	size = count_vars(&params[0]);
	i = 0;
	while (i < size)
	{
		array = ft_split_lars(params[i], '=', &test); //rename to ft_split
		if (!array)
			return (0); //malloc
		if (!trim_strings(&dst_name, &dst_content, array))
			return (0); //malloc
		if (!find_env_var_name(&v->env_head, &dst_name, &dst_content))
		{
			env__ft_lstadd_back(&v->env_head, env__ft_lstnew(dst_name, dst_content));
			env__ft_lstmove_back("_", v->env_head);	
		}
		i++;
	}
	ft_printf("Export check1\n");
	v->has_env_changed = 1;
	return (1);
}