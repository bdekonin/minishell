/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_environment_variable.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 10:10:40 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/09/09 15:14:04 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline size_t findspace(char *str)
{
	size_t i;
	
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '/' && str[i] != '\n')
		i++;
	return (i);
}

char *find_environment_variable(t_vars *v, char *var, size_t *len)
{
	t_list	*lst;
	t_env	*tmp;
	size_t	length;

	// if (*var == '?')
	// {
	// 	if (!v->history_head)
	// 		return ("0");
	// 	else
	// 		return (his__ft_lstlast(v->history_head)->ret);
	// }
	// else if (*line == '$')
	// 	return (v->__parentpid); // change to current pid
	if (!len)
		length = findspace(var);
	else
		length = *len;
	lst = v->env;
	while (lst)
	{
		tmp = lst->content;
		if (!ft_strncmp(tmp->name, var, length))
			return (tmp->content);
		lst = lst->next;
	}
	return (NULL);
}
