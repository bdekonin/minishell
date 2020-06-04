/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_environment_variable.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 10:10:40 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/04 10:11:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** Returns the read environment variable
**
** @param  t_vars *v	vars
** @param  char *line	Pointer to string after the $
**
** @return char*		Returns pointer of environment variable
*/

char *find_environment_variable(t_vars *v, char *line)
{
	t_env		*lst;
	int			j;
	char		*name;

	if (*line == '?')
		return (v->history_head->output);
	name = ft_strdup(line);
	if (!name)
		return (NULL);
	j = 0;
	lst = v->env_head;
	while (name[j] && name[j] != ' ' && name[j] != '/' && name[j] != '|' \
	&& name[j] != '>') // change to flags
		j++;
	name[j] = '\0';
	while (lst)
	{
		if (!ft_strncmp(lst->name, name, ft_strlen(name)))
		{
			free(name);
			return (lst->content);
		}
		lst = lst->next;
	}
	free(name);
	return (v->__homedir);
}
