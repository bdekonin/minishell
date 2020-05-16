/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 11:34:38 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/16 17:55:28 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../main.h"

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
