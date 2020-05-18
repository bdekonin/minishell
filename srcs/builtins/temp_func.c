/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/18 21:21:56 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

// cd

// int pwd(t_vars *v, char **params)
// {
// 	char *teeest = malloc(sizeof(char) * 1024);
// 	if (params[1] && ft_strncmp(params[1], ";", 3))
// 	{
// 		errno = 7;
// 		perror(error);
// 		exit(EXIT_FAILURE);
// 	}
// 	teeest = getcwd(teeest, path_max);
// 	ft_printf("%s\n", teeest);
// 	// for (int i = 0; params[i + 1]; i++)
// 	// {
// 	// 	ft_printf("argv[%d] - [%s]\n", i, params[i]);
// 	// }
// 	if (params[1] && params[2] && !ft_strncmp(params[1], ";", 3))
// 		cmd(v, params + 2);
// 	return (1);
// }

// int export(t_vars *v, char **params)
// {
// 	printf("%s - %s\n", v->argv[0], params[0]);
// 	return (1);
// }
int unset(t_vars *v, char **params)
{
	v->has_env_changed = 1;
	env__ft_lstremove_middle(params[1], v->env_head);
	return (1);
}
int env(t_vars *v, char **params)
{
	t_env *env;
	printf("%s - %s\n", v->argv[0], params[0]);
	env = v->env_head;
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	return (1);
}
int exitt(t_vars *v, char **params)
{
	printf("%s - %s\n", v->argv[0], params[0]);
	exit(EXIT_SUCCESS);
	return (1);
}
int help(t_vars *v, char **params)
{
	printf("%s - %s\n", v->argv[0], params[0]);
	return (1);
}
