/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 12:26:08 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/16 17:59:44 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

void	env__ft_lstadd_front(t_env **alst, t_env *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}
