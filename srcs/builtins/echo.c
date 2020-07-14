/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:33:04 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/07/14 17:11:30 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int check_newline_option(char *param)
{
	int newline_opt;

	if (!ft_strncmp(param, "-n", 3))
	newline_opt = 1;
	else
	newline_opt = 0;
	return (newline_opt);
}

static char *trim_string(char *src)
{
	char *dst;
	char set[3];

	set[0] = 34;
	set[1] = 39;
	set[2] = 0;
	dst = ft_strtrim(src, set);
	printf("src = [%s]\ndst = [%s]\n", src, dst);
	return (dst);
}

int echo(t_vars *v, t_cmd *cmd, char **params)
{
	int i = 0;
	int fd = 1;
	int newline_opt;
	ssize_t write_ret;
	char *str;

	newline_opt = check_newline_option(params[i]);
	i += newline_opt;
	while (params[i])
	{
		str = trim_string(params[i]);
		if (!str)
			return (1);
		write_ret = write(fd, str, ft_strlen(str));
		free(str);
		if (write_ret < 0 || write_ret != ft_strlen(str))
			return (1);
		i++;
	}
	if (!newline_opt && write(fd, "\n", 1) != 1)
		return (1);
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}