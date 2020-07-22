/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_environment_variable.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 10:10:40 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/22 09:25:50 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** Returns the read environment variable
**
** @param  t_vars *v	vars							 ↓
** @param  char *line	Points to character after $ (cd $PATH)
**
** @return char*		Returns pointer of environment variable (DONT FREE)
*/

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
	t_env	*temp;
	size_t	length;

	if (*var == '?')
	{
		if (!v->history_head)
			return ("0");
		else
			return (v->history_head->ret);
	}
	// else if (*line == '$')
	// 	return (v->__parentpid); // change to current pid
	if (!len)
		length = findspace(var);
	else
		length = *len;
	temp = v->env_head;
	while (temp)
	{
		if (!ft_strncmp(temp->name, var, length))
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}
