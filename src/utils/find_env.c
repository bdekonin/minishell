/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 13:54:53 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/29 21:14:48 by lverdoes      ########   odam.nl         */
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
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

t_env		*find_env(t_vars *v, char *identifier, size_t *len)
{
	t_env	*node;
	size_t	length;

	if (!len)
		length = find_identifier_len(identifier);
	else
		length = *len;
	node = v->env;
	while (node)
	{
		if (!ft_strncmp(node->name, identifier, length + 1))
			return (node);
		node = node->next;
	}
	return (NULL);
}
