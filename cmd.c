/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/04 13:48:45 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char		*cmd_str(int i)
{
	char	*cmd_str[bultins + 1];

	cmd_str[0] = "echo";
	cmd_str[1] = "cd";
	cmd_str[2] = "pwd";
	cmd_str[3] = "export";
	cmd_str[4] = "unset";
	cmd_str[5] = "env";
	cmd_str[6] = "exit";
	cmd_str[7] = "help";
	cmd_str[8] = NULL;
	return (cmd_str[i]);
}

int run_command(t_vars *v, char **params)
{
	int i = 0;
	v->flag_i = 0;

	int (*p[8]) (t_vars *v, char **params);
	p[0] = echo;
	p[1] = cd;
	p[2] = pwd;
	p[3] = exportt;
	p[4] = unset;
	p[5] = env;
	p[6] = exitt;
	p[7] = help;
	param_to_lower_case(params[0]);
	while (i < bultins)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 15))
			return ((*p[i])(v, params + 1));
		i++;
	}
	ft_printf(cmd_notfound, v->__executable + 2, params[0]);
	v->argument_ret = ft_strdup("0"); // maybe 1?
	if (!v->argument_ret)
		return (0);
	return (1);
}

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
		his__ft_lstadd_front(&v->history_head, his__ft_lstnew(ft_strdup(argv[v->i]), ft_strdup(v->argument_ret), v->line));
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
