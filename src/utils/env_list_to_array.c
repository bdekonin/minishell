/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_to_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/12 16:59:08 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/14 14:44:26 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **env_list_to_array(t_vars *v)
{
	char	**envp;
	t_list	*tmp;
	t_env	*node;
	size_t	i;

	envp = ft_calloc(ft_lstsize(v->env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = v->env;
	while (tmp)
	{
		node = tmp->content;
		envp[i] = ft_strxjoin(node->name, "=", node->content, NULL);
		if (!envp[i])
		{
			ft_free_array((void **)envp, i);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	return (envp);
}
