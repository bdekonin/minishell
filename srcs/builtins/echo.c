/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 20:38:50 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/17 22:15:30 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** https://stackoverflow.com/questions/7656549/understanding-requirements-for-execve-and-setting-environment-vars
*/

int echo(t_vars *v, char **params)
{
	int stat;
	// ft_printf("%d\t%s\n%d\t%s\n", 0, params[0], 1, params[1]);
	pid_t spoon = fork();
	if (!spoon)
	{
		execve("/bin/echo", &params[0], v->envp);
	}
	wait(&stat);
	return (1);
}