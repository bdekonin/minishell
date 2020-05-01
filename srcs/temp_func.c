/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/01 21:59:05 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
int echo(t_vars *v, char **params)
{
	printf("%s - %s\n", v->argv[0], params[0]);
	return (1);
}
// cd
int pwd(t_vars *v, char **params)
{
	int k = amountofsplits(v, params);
	ft_printf("k = %d\n", k);
	if (k >= 1 && ft_strncmp(params[1], ";", 3))
	{
		errno = 7;
		perror(error);
		exit(EXIT_FAILURE);
	}
	ft_printf("%s\n", v->current_path);
	for (int i = 0; i < k; i++)
	{
		ft_printf("arg[%d] - [%s]", i, params[i]);
	}
	if (k >= 1 && !ft_strncmp(params[1], ";", 3))
		cmd(v, params + 2);
	return (1);
}
int export(t_vars *v, char **params)
{
	printf("%s - %s\n", v->argv[0], params[0]);
	return (1);
}
int unset(t_vars *v, char **params)
{
	printf("%s - %s\n", v->argv[0], params[0]);
	return (1);
}
int env(t_vars *v, char **params)
{
	printf("%s - %s\n", v->argv[0], params[0]);
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