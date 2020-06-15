/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/15 16:25:03 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// static int read_locations(char *str)
// {
// 	int fd;
// 	int ret;
// 	char *line;

// 	ret = 1;
// 	fd = open("srcs/utils/location_commands/bin.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (-1);
// 	while (ret > 0)
// 	{
// 		ret = get_next_line(fd, &line);
// 		if (ret < 0)
// 			return (-1);
// 		if (!ft_strncmp(line, str, ft_strlen(str)))
// 		{
// 			ft_printf("Command found - [%s]\n", line);
// 			return (1);
// 		}
// 		free(line);
// 	}
// 	close(fd);
// 	ft_printf("Command not found\n");
// 	return (0);
// }

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
	cmd_str[7] = "debug";
	cmd_str[8] = NULL;
	return (cmd_str[i]);
}

int run_command(t_vars *v, char **params, t_node *node)
{
	int i = 0;

	int (*p[8]) (t_vars *v, t_node *node, char **params);
	p[0] = echo;
	p[1] = cd;
	p[2] = pwd;
	p[3] = exportt;
	p[4] = unset;
	p[5] = env;
	p[6] = exitt;
	p[7] = debug;
	ft_str_tolower(params[0]);
	while (i < bultins)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 15))
			return ((*p[i])(v, node, params + 1));
		i++;
	}
	// if (read_locations(params[0]))
	// 	ft_execve(v, ft_strjoin("/bin/", params[0]), params);
	// else
		ft_printf(cmd_notfound, v->__executable + 2, params[0]);
	v->argument_ret = ft_strdup("0"); // maybe 1?
	if (!v->argument_ret)
		return (0);
	return (-1);
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

int run_cmd(t_vars *v, t_node *node)
{
	char	**args;
	int		size[2];

	while (node)
	{
		v->flag_i = 0;
		args = ft_split_lars(node->line, ' ', &size[0]);
		if (!run_command(v, args, node))
			return (0);
		his__ft_lstadd_front(&v->history_head, his__ft_lstnew(ft_strdup(node->line), ft_strdup(v->argument_ret), ft_strdup(v->line))); // protect
		if (node->line[node->i] == '|' || node->line[node->i] == '>')
		{
			// ft_printf("found a flag [%s]\n", node->line + node->i);
		}
		free(v->argument_ret);
		ft_free_array((void*)args, size[0]);
		node = node->next;
	}
	return (1);
}

void	read_user_input(t_vars *v)
{
	int size;
	char **argv_semicolen;
	char	*trimline;
	t_history	*history;

	history = __init_set_history(v);
	ft_printf(v->prefix, v->__logname, ft_strrchr(v->current_path, '/') + 1);
	v->ret = get_next_line(STDIN_FILENO, &v->line);
	if (v->ret < 0)
		exit(1);
	if (*v->line != 0) // so it doesnt do any bullshit if line is empty
	{
		v->i = 0;
		argv_semicolen = ft_split_lars(v->line, ';', &size);
		for (int j = 0; j < size; j++)
		{
			trimline = ft_strtrim(argv_semicolen[j], " \t");
			if (!trimline)
				return ; // free llist
			node__ft_lstadd_back(&v->nodehead, node__ft_lstnew(';', 0, trimline));
		}
		if (!v->argv)
			exit(EXIT_FAILURE);
		if (!run_cmd(v, v->nodehead->next))
			exit(EXIT_FAILURE);
		ft_free_array((void*)argv_semicolen, size);
	}
	free(v->line);
}
// cd ..  | echo | pwd ; env && env ; env