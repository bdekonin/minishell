/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_run_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/02 17:44:13 by bdekonin      ########   odam.nl         */
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
	int i;
	int (*p[8]) (t_vars *v, t_cmd *cmd, char **params, char **ret);

	i = 0;
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

static int confirm_flags(t_vars *v, t_cmd *cmd)
{
	char	*line;
	int		fd;
	// if (cmd->type == PIPE)
	// 	ft_printf("\x1B[36m[|] NOW\n\x1B[0m");
	// else if (cmd->type == RDIRLEFT)
	// 	ft_printf("\x1B[36m[<] NOW\n\x1B[0m");
	// else if (cmd->type == RDIRRIGHT)
	// 	ft_printf("\x1B[36m[>] NOW\n\x1B[0m");
	if (cmd->type && !cmd->next)
	{
		ft_printf("\x1B[31mMissing next command.\n\x1B[0m");
		if (cmd->type == PIPE)
		{
			ft_printf("pipe> ");
			get_next_line(STDIN_FILENO, &line); // make while loop
			free(line);
		}
		if (cmd->type == RDIRLEFT || cmd->type == RDIRRIGHT)
		{
			ft_printf("%s: parse error near `\\n'\n", v->__executable + 2);
		}
	}
	else if (cmd->type == RDIRLEFT)
	{
		fd = open(cmd->next->line, O_RDONLY);
		if (fd < 0)
			ft_printf("%s: %s: No such file or directory\n", \
						v->__executable + 2, cmd->next->line);
	}
}

/*
** call this command.
**
*/
int run_cmd(t_vars *v, t_cmd *cmd)
{
	char	*ret = NULL;
	char	**args;
	size_t	splitsize;

	while (cmd)
	{
		args = ft_split_sep(cmd->line, " \t", &splitsize);
		confirm_flags(v, cmd);
		if (!run_command(v, args, cmd, &ret))
			return (0);
		sethistory(&v->history_head, v->line, ret, cmd->line);
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
			{
				env__ft_lstclear(&v->env_head, free);
				his__ft_lstclear(&v->history_head, free); // DO THIS
				node__ft_lstclear(&v->nodehead, free);
				exit(EXIT_FAILURE);
			}
			node = node->next;
		}
	}
	free(v->line);
}
// cd ..  | echo | pwd ; env < test.txt ; env