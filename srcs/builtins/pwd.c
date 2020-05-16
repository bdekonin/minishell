/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/16 17:53:05 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int pwd(t_vars *v, char **params)
{
	char *str;

	if (params[1] && ft_strncmp(params[1], ";", 3))
	{
		errno = 7;
		perror(error);
		exit(EXIT_FAILURE);
	}
	str = NULL;
	str = getcwd(str, 0);
	if (!str)
	{
		perror(error);
		exit(EXIT_FAILURE);
	}
	ft_printf("%s\n", str);
	free(str);
	if (params[1] && params[2] && !ft_strncmp(params[1], ";", 3))
		cmd(v, params + 2);
	return (1);
}
