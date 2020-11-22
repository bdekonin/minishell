/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:43:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:15:40 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

void	env__ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env *last;

	if (!new)
		return ;
	if (*alst)
	{
		last = env__ft_lstlast(*alst);
		last->next = new;
	}
	else
		env__ft_lstadd_front(alst, new);
}
