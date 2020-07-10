/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/10 21:23:15 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** https://man7.org/linux/man-pages/man1/pwd.1p.html
**
**	EXIT STATUS         top
**  The following exit values shall be returned:
**  0    Successful completion.
**  >0    An error occurred.
*/

int pwd(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	v->current_path = getcwd(v->current_path, PATH_MAX);
	if (!v->current_path)
		ft_printf("ERROR\n");
	else
		*ret = ft_strdup(v->current_path);
	ft_printf("%s\n", v->current_path);
	(void)(params);
	(void)(cmd);
	return (1);
}

int echo(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	ft_printf("%.0s\t", v->executable__->content);
	for (int i = 0; params[i]; i++)
		ft_printf("echo\t%s\n", params[i]);
	*ret = ft_strdup("1");
	(void)(params);
	(void)(cmd);
	return (1);
}

// The return status is zero unless a name does not exist or is readonly.
int unset(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	env__ft_lstremove_middle(params[0], v->env_head);
	*ret = ft_strdup("1");
	if (!*ret)
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}

int env(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	t_env *env;

	env = v->env_head;
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	*ret = ft_strdup("1");
	if (!*ret)
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}
