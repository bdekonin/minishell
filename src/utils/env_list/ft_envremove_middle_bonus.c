/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envremove_middle_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:43:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:16:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

void env__ft_lstremove_middle(char *name, t_env *new)
{
	t_env *back;

	while (new)
	{
		if (!ft_strncmp(name, new->name, ft_strlen(new->name)))
		{
			back->next = new->next;
			free(new->name);
			free(new->content);
			free(new);
			break ;
		}
		back = new;
		new = new->next;
	}
}
