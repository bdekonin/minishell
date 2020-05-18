/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/17 20:38:50 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/18 18:40:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** https://stackoverflow.com/questions/7656549/understanding-requirements-for-execve-and-setting-environment-vars
*/

int echo(t_vars *v, char **params)
{
	ft_execve(v, "/bin/echo", params);
	return (1);
}