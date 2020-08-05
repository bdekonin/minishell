/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:33:04 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/08/05 13:48:30 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static size_t	check_newline_option(char **params, int *newline_opt)
{
	size_t i;

	i = 0;
	if (!ft_strncmp(params[i], "-n", 3))
	{
		*newline_opt = 1;
		i++;
	}
	else
		*newline_opt = 0;
	while (params[i] && !ft_strncmp(params[i], "-n", 3))
		i++;
	return (i);
}

int echo(t_vars *v, t_cmd *cmd, char **params)
{
	size_t i;
	int newline_opt;
	ssize_t ret;
	char *dst;
	char *tmp;

	i = check_newline_option(params, &newline_opt);
	if (params[i])
	{
		dst = ft_strdup(params[i]);
		i++;
	}
	else
		dst = ft_strdup("\0");
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
