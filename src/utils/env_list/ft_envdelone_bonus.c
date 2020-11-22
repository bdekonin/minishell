/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envdelone_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 12:51:19 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:16:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

void	env__ft_lstdelone(t_env *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
	{
		del(lst->name);
		del(lst->content);
	}
	free(lst);
}
