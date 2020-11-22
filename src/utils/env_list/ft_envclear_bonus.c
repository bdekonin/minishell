/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 15:25:54 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:16:19 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

void	env__ft_lstclear(t_env **lst, void (*del)(void*))
{
	t_env		*tmp;

	if (!lst)
		return ;
	if (del)
		while (*lst)
		{
			tmp = (*lst)->next;
			env__ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	*lst = NULL;
}
