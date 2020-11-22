/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:36:51 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/22 17:24:55 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_vars *v, char **params)
{
	t_env   *node;
	size_t  size;

	node = v->env;
	size = ft_array_size((const char **)params);
	if (size == 0)
	{
		while (node)
		{
			ft_printf("%s=%s\n", node->name, node->content);
			node = node->next;
		}
	}
	else
		return (run_command(v, params)); //ja dit hoeft dus toch niet (zie subject)
	return (0);
}
