/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 20:35:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/11 11:52:53 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static char **__make_array(t_vars *v, int size, t_env *list);
static char **__linkedlist_to_array(t_vars *v, int *list_size);

static char **make_param()
{
	char **arr;

	arr = malloc(sizeof(char*) * 3);
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup("leaks");
	arr[1] = ft_itoa(getpid());
	if (!arr[0])
		return (NULL);
	arr[2] = NULL;
	return (arr);
}

static void				leaks(t_vars *v)
{
	char **arr;
	arr = make_param();

	if (!arr)
		return ;
	ft_execve(v, "/usr/bin/leaks", arr);
}

static void				pid(void)
{
	ft_printf("---- Process Pids ----\n");
	ft_printf("Parent Process\t%d\nChild Process\t%d\n\n", getppid(), getpid());
}

static void				his(t_vars *v)
{
	t_history *his;

	his = v->history_head;
	ft_printf("---- History list ----\n");
	ft_printf("[%s]\t[%s]\t[%s]\n", v->line, v->argv[v->i], "???");
	while (his)
	{
		ft_printf("[%s]\t[%s]\t[%s]\n", his->line, his->command, his->output);
		his = his->next;
	}
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

int						debug(t_vars *v, char **params)
{
	if ((params[0] && !ft_strncmp(params[0], "leaks", 7)) || !params[0])
		leaks(v);
	// if ((params[0] && !ft_strncmp(params[0], "pid", 4)) || !params[0])
	// 	pid();
	// if ((params[0] && !ft_strncmp(params[0], "history", 9)) || !params[0])
	// 	his(v);
	// else
	// {
	// 	v->argument_ret = ft_strdup("1");
	// 	// malloc protect
	// 	return (0);
	// }
	v->argument_ret = ft_strdup("1");
	return (1);
}