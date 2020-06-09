/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 20:35:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/08 22:00:25 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static void				leaks(void)
{
	char *str;
	char *str2;

	ft_printf("---- Leaks ----\n");
	ft_printf("Parent\n");
	str = ft_itoa(getppid());
	str2 = ft_strjoin("leaks ", str);
	free(str);
	str = ft_strjoin(str2, " | tail -2");
	system(str);
	free(str2);
	free(str);
	ft_printf("Child\n");
	str = ft_itoa(getpid());
	str2 = ft_strjoin("leaks ", str);
	free(str);
	str = ft_strjoin(str2, " | tail -2");
	system(str);
	free(str2);
	free(str);
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
		leaks();
	if ((params[0] && !ft_strncmp(params[0], "pid", 4)) || !params[0])
		pid();
	if ((params[0] && !ft_strncmp(params[0], "history", 9)) || !params[0])
		his(v);
	else
	{
		v->argument_ret = ft_strdup("1");
		// malloc protect
		return (0);
	}
	v->argument_ret = ft_strdup("1");
	return (1);
}