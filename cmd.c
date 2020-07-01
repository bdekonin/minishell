/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/01 12:50:04 by bdekonin      ########   odam.nl         */
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
	cmd_str[7] = "debug";
	cmd_str[8] = NULL;
	return (cmd_str[i]);
}

int run_command(t_vars *v, char **params, t_node *node, char **ret)
{
	int i = 0;

	int (*p[8]) (t_vars *v, t_node *node, char **params, char **ret);
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
			return ((*p[i])(v, node, params + 1, ret));
		i++;
	}
	// i = ft_execve(v, node, params, ret);
	// if (!i)
	// 	return (0);
	// else if (i)
	// 	return (1);
	ft_printf(cmd_notfound, v->__executable + 2, params[0]);
	*ret = ft_strdup("0"); // maybe 1?
	if (!*ret)
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

// cd ..  | cd .. | cd ..

int run_cmd(t_vars *v, t_node *node)
{
	t_node	*newnode;
	char	*ret = NULL;
	char	**args;
	size_t	splitsize;
	
	while (node)
	{
		args = ft_split_sep(node->line, " \t", &splitsize);
		if (!run_command(v, args, node, &ret))
			return (0);
			// fork here
		node->i += findflag(node->line, "|><");
		{
			newnode = node__ft_lstnew(node->line[node->i], 0, node->line + (node->i + 1));
			// // if (!newnode)
			// // 	return (0);
			run_cmd(v, newnode);
			// if (!runcmd)
		}
		// ft_printf("")
		// free(ret);
		ft_free_array((void*)args, (int)splitsize);
		node = node->next;
	}
	return (1);
}

int ft_split_input(t_vars *v);

void	read_user_input(t_vars *v)
{
	size_t		splitsize;
	char		**argv_semicolen;
	char		*trimline;
	t_history	*history;

	history = __init_set_history(v);
	ft_printf(v->prefix, v->__logname->content, ft_strrchr(v->current_path, '/') + 1);
	v->ret = get_next_line(STDIN_FILENO, &v->line);
	if (*v->line != 0) // so it doesnt do any bullshit if line is empty
	{
		ft_split_input(v);
		// if (ft_split_input)
		exit(1);
		if (!run_cmd(v, v->nodehead->next))
			exit(EXIT_FAILURE);
	}
	free(v->line);
}
// cd ..  | echo | pwd ; env < test.txt ; env