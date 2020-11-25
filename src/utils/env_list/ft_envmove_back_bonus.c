/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envmove_back_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:43:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/23 21:46:00 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

void	env__ft_lstmove_back(char *name, t_env *new)
{
	t_env *back;
	t_env *last;

	if (!new)
		return ;
	while (new)
	{
		if (!ft_strncmp(name, new->name, ft_strlen(new->name)))
		{
			back->next = new->next;
			last = env__ft_lstlast(new);
			last->next = new;
			new->next = NULL;
			break ;
		}
		back = new;
		new = new->next;
	}
}
