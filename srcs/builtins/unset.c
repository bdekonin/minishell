/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 11:05:24 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/08/05 11:22:36 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

// The return status is zero unless a name does not exist or is readonly.
int unset(t_vars *v, t_cmd *cmd, char **params)
{
	size_t i;

	i = 0;
	while (params[i])
	{
		env__ft_lstremove_middle(params[i], v->env_head);
		i++;
	}
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}