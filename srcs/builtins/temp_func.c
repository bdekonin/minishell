/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/28 23:21:13 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int pwd(t_vars *v, t_node *node, char **params, char **ret)
{
	v->current_path = getcwd(v->current_path, PATH_MAX);
	if (!v->current_path)
		ft_printf("ERROR\n");
	else
		*ret = ft_strdup(v->current_path);
	ft_printf("%s\n", v->current_path);
	(void)(params);
	(void)(node);
	return (1);
}

int echo(t_vars *v, t_node *node, char **params, char **ret)
{
	ft_printf("%.0s\t", v->__executable);
	for (int i = 0; params[i]; i++)
		ft_printf("echo\t%s\n", params[i]);
	*ret = ft_strdup("1");
	(void)(params);
	(void)(node);
	return (1);
}

// The return status is zero unless a name does not exist or is readonly.
int unset(t_vars *v, t_node *node, char **params, char **ret)
{
	env__ft_lstremove_middle(params[0], v->env_head);
	*ret = ft_strdup("1");
	(void)(params);
	(void)(node);
	return (1);
}

int env(t_vars *v, t_node *node, char **params, char **ret)
{
	t_env *env;

	env = v->env_head;
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	*ret = ft_strdup("1");
	(void)(params);
	(void)(node);
	return (1);
}

int exitt(t_vars *v, t_node *node, char **params, char **ret)
{
	env__ft_lstclear(&v->env_head, free);
	his__ft_lstclear(&v->history_head, free); // DO THIS
	node__ft_lstclear(&v->nodehead, free); // reset the list.
	exit(EXIT_SUCCESS);
	(void)(params);
	(void)(node);
	(void)(ret);
	return (1);
}
