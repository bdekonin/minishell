/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/03 11:57:22 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_history *__init_set_history(t_vars *v)
{
	static int init;
	t_history *lst;

	if (!init)
	{
		lst = his__ft_lstnew(ft_strdup(""), ft_strdup(""), ft_strdup(""));
		v->history_head = lst;
		init++;
	}
	return (v->history_head);
}

int run_cmd(t_vars *v, char **argv)
{
	char	**args;
	int		size;
	t_history *history;

	history = __init_set_history(v);
	v->i = 0;
	while (argv[v->i])
	{
		args = ft_split_lars(argv[v->i], ' ', &size);
		if (!run_command(v, args))
			return (0);
		his__ft_lstadd_front(&v->history_head, his__ft_lstnew(ft_strdup(argv[v->i]), ft_strdup(v->argument_ret), v->line)); // will crash because if argument has been passed twice then it will free the first one which will segfault the next
		v->flag_i = ft_charsearch(v->argv[v->i], '|'); // only | add others aswell
		if (v->flag_i)
			ft_printf("FLAG FOUND HERE [%s]\n", argv[v->i] + v->flag_i);
		ft_free_array((void*)args, size);
		free(v->argument_ret);
		v->i++;
	}
	return (1);
}

void	read_user_input(t_vars *v)
{
	int size;

	v->forky = fork();
	while (!v->forky)
	{
		ft_printf(v->prefix, v->__logname, ft_strrchr(v->current_path, '/') + 1);
		v->ret = get_next_line(STDIN_FILENO, &v->line);
		if (v->ret < 0)
			exit(1);
		if (*v->line != 0)
		{
			v->argv = ft_split_lars(v->line, ';', &size);
			if (!v->argv)
				exit(EXIT_FAILURE);
			if (!run_cmd(v, v->argv))
				exit(EXIT_FAILURE);
			ft_free_array((void*)v->argv, size);
		}
	}
}
