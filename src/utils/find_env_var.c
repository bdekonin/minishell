/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_env_var.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 13:54:53 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 13:28:52 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t		find_identifier_len(char *str)
{
	size_t i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
		return (i);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char		*find_env_var(t_vars *v, char *identifier, size_t *len)
{
	t_list  *lst;
	t_env   *tmp;
	size_t  length;

	if (!len)
		length = find_identifier_len(identifier);
	else
		length = *len;
	lst = v->env;
	while (lst)
	{
		tmp = lst->content;
		if (!ft_strncmp(tmp->name , identifier, length)) //or length + 1?
			return (tmp->content);
		lst = lst->next;
	}
	return (NULL);
}
