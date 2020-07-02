/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/02 10:38:34 by bdekonin      ########   odam.nl         */
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

int run_command(t_vars *v, char **params, t_cmd *cmd, char **ret)
{
	int i = 0;

	int (*p[8]) (t_vars *v, t_cmd *cmd, char **params, char **ret);
	p[0] = echo;
	p[1] = cd;
	p[2] = pwd;
	p[3] = exportt;
	p[4] = unset;
	p[5] = env;
	p[6] = exitt;
	p[7] = debug;
	ft_str_tolower(params[0]);
	ft_printf("Type = [%c]\n", cmd->type);
	while (i < bultins)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 15))
			return ((*p[i])(v, cmd, params + 1, ret));
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

int sethistory(t_history **his, char *fullcommand, char *ret, char *singlecommand)
{
	t_history *newlist;
	if (!*his)
	{
		*his = his__ft_lstnew(ft_strdup(singlecommand), ret, ft_strdup(fullcommand)); // protect
		if (!*his)
			return (0);
		else
			return (1);
	}
	else
	{
		newlist = his__ft_lstnew(ft_strdup(singlecommand), ret, ft_strdup(fullcommand)); // protect
		his__ft_lstadd_front(&*his, newlist);
	}
}

int run_cmd(t_vars *v, t_cmd *cmd)
{
	// t_node	*newnode;
	char	*ret = NULL;
	char	**args;
	size_t	splitsize;
	
	while (cmd)
	{
		args = ft_split_sep(cmd->line, " \t", &splitsize);
		if (!run_command(v, args, cmd, &ret))
			return (0);
			// fork here
		sethistory(&v->history_head, v->line, ret, cmd->line);
		// ft_printf("%s\n", v->history_head->line);
		// ft_printf("")
		// free(ret);
		ft_free_array((void*)args, (int)splitsize);
		cmd = cmd->next;
	}
	return (1);
}

int ft_split_input(t_vars *v);

void	read_user_input(t_vars *v)
{
	t_node *node;

	ft_printf(v->prefix, v->__logname->content, ft_strrchr(v->current_path, '/') + 1);
	v->ret = get_next_line(STDIN_FILENO, &v->line);
	if (*v->line != 0) // so it doesnt do any bullshit if line is empty
	{
		ft_split_input(v);
		node = v->nodehead;
		while (node)
		{
			if (!run_cmd(v, node->cmd))
				exit(EXIT_FAILURE);
			node = node->next;
		}
	}
	free(v->line);
}
// cd ..  | echo | pwd ; env < test.txt ; env