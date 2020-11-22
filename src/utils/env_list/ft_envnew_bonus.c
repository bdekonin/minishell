/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/22 17:16:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../minishell.h"

t_env	*env__ft_lstnew(void *name, void *content)
{
	t_env *tmp;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (0);
	tmp->content = content;
	tmp->name = name;
	tmp->next = NULL;
	return (tmp);
}
