/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:32:07 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:16:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

int	env__ft_lstsize(t_env *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
