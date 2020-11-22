/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 12:26:08 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:16:16 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

void	env__ft_lstadd_front(t_env **alst, t_env *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}
