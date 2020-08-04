/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:33:04 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/08/04 11:12:34 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int check_newline_option(char *param)
{
	if (!ft_strncmp(param, "-n", 3))
		return (1);
	return (0);
}

int echo(t_vars *v, t_cmd *cmd, char **params)
{
	size_t i;
	int newline_opt;
	ssize_t ret;
	char *dst;
	char *tmp;

	// int z = 0; //debug
	// while (params[z]) //debug
	// {
	// 	printf("params[%d] = [%s]\n", z, params[z]);
	// 	z++;
	// }
	newline_opt = check_newline_option(params[0]);
	i = newline_opt;
	if (params[i])
	{
		dst = ft_strdup(params[i]);
		i++;
	}
	while (params[i])
	{
		tmp = ft_strxjoin(dst, " ", params[i], NULL);
		free(dst);
		dst = tmp;
		i++;
	}
	ret = write(1, dst, ft_strlen(dst));
	free(dst);
	if (ret < 0 || (size_t)ret != ft_strlen(dst))
		return (0); //write error
	if (newline_opt == 0 && write(1, "\n", 1) != 1)
		return (0);
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}
