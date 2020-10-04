/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_flags.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 17:56:43 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/24 17:56:51 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_spaces_around_flags(t_vars *v, char **arg, size_t i)
{
	char *tmp;
	
	if (!ft_strncmp((*arg) + i, ">>", 2))
		tmp = ft_strexpand(*arg, "*>>*", *arg + i, 2);
	else if ((*arg)[i] == '|')
		tmp = ft_strexpand(*arg, "*|*", *arg + i, 1);
	else if ((*arg)[i] == '>')
		tmp = ft_strexpand(*arg, "*>*", *arg + i, 1);
	else if ((*arg)[i] == '<')
		tmp = ft_strexpand(*arg, "*<*", *arg + i, 1);
	else
		tmp = NULL;
	if (!tmp)
		ft_exit_error(v, EXIT_FAILURE);
	free(*arg);
	*arg = tmp;
}

size_t  find_flags(t_vars *v, char **arg)
{
	size_t i;

	i = 0;
	while ((*arg)[i] != '\0')
	{
		if (ft_charsearch((*arg)[i], FLAGS))
		{
			put_spaces_around_flags(v, arg, i);
			i += 3;
		}
		i++;
	}
	return (0);
}