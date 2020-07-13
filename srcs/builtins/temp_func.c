/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/13 18:08:14 by bdekonin      ########   odam.nl         */
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

int pwd(t_vars *v, t_cmd *cmd, char **params)
{
	v->current_path = getcwd(v->current_path, PATH_MAX);
	if (!v->current_path)
		ft_printf("ERROR\n");
	else
		if (!sethistory(&v->history_head, v->line, v->current_path))
			return (0);
	ft_printf("%s\n", v->current_path);
	(void)(params);
	(void)(cmd);
	return (1);
}

int echo(t_vars *v, t_cmd *cmd, char **params)
{
	ft_printf("%.0s\t", v->__executable->content);
	for (int i = 0; params[i]; i++)
		ft_printf("echo\t%s\n", params[i]);
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}

// The return status is zero unless a name does not exist or is readonly.
int unset(t_vars *v, t_cmd *cmd, char **params)
{
	env__ft_lstremove_middle(params[0], v->env_head);
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}

int env(t_vars *v, t_cmd *cmd, char **params)
{
	t_env *env;

	env = v->env_head;
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}
