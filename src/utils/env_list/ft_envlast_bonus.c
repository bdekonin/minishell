/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:38:32 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:16:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

t_env	*env__ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
