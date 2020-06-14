/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 20:35:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/14 10:21:59 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** Makes usable array for leaks
**
** @param  N/A
**
** @return char **		{leaks},
**						{minishell},
**						{NULL}
*/

static char				**make_param(char *ppid)
{
	char **arr;

	arr = malloc(sizeof(char*) * 3);
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup("leaks");
	if (!arr[0])
	{
		ft_free_array((void*)arr, 1);
		return (NULL);
	}
	arr[1] = ft_strdup(ppid);
	if (!arr[1])
	{
		ft_free_array((void*)arr, 2);
		return (NULL);
	}
	arr[2] = NULL;
	return (arr);
}

/*
** Uses ft_execve to launch the leaks binary file.
**
** @param  t_vars *v		vars
**
** @return int				0 = correct
*/

static int				leaks(t_vars *v)
{
	char **arr;

	arr = make_param(v->__ppid);
	if (!arr)
		return (1);
	ft_execve(v, "/usr/bin/leaks", arr);
	ft_free_array((void*)arr, 3);
	ft_printf("\n");
	return (0);
}

/*
** Prints out the history of Lines Commands and Outputs.
**
** @param  t_vars *v		vars
**
** @return int				0 = correct
*/

static int				his(t_vars *v)
{
	t_history *his;

	his = v->history_head;
	ft_printf("---- History list ----\nLines\t\t\t\tCommands\t\t\t\tOutput\n");
	ft_printf("[%s]\t\t\t\t[%s]\t\t\t\t[%s]\n", v->line, v->argv[v->i], "1");
	while (his)
	{
		ft_printf("[%s]\t\t\t\t[%s]\t\t\t\t[%s]\n", \
								his->line, his->command, his->output);
		his = his->next;
	}
	return (0);
}

/*
** Shows importent information such as, current pids & leaks & history
**
** @param  t_vars *v		vars
** @param  char **params	all the arguments after the command
**
** @return int				1 = correct \
**							0 = invalid argument \
**							-1 = malloc fail
*/

int						debug(t_vars *v, char *line, char **params)
{
	int ret;

	ret = 0;
	if ((params[0] && !ft_strncmp(params[0], "leaks", 7)) || !params[0])
		ret += leaks(v);
	if ((params[0] && !ft_strncmp(params[0], "history", 9)) || !params[0])
		ret += his(v);
	v->argument_ret = (ret) ? ft_strdup("0") : ft_strdup("1");
	if (!v->argument_ret)
		return (0);
	(void)line;
	return (1);
}
