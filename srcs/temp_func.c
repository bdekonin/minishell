/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_func.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/30 18:53:55 by bdekonin      ########   odam.nl         */
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
	printf("%s\n", v->current_path);
	params++;
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