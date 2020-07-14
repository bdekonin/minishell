/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_run_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/14 17:19:49 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline int reset_fd(t_vars *v)
{
	dup2(v->fd, STDOUT_FILENO);
	dup2(v->stdout_copy, 1);
	close(v->stdout_copy);
	v->stdout_copy = 0;
	return (1);
}

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

int run_command(t_vars *v, char **params, t_cmd *cmd)
{
	if (cmd->prev && cmd->type != PIPE)
		return (1);
	int i;
	int (*p[8]) (t_vars *v, t_cmd *cmd, char **params); 

	i = 0;
	p[0] = echo;
	p[1] = cd;
	p[2] = pwd;
	p[3] = exportt;
	p[4] = unset;
	p[5] = env;
	p[6] = ft_exit;
	p[7] = debug;
	ft_str_tolower(params[0]);
	while (i < bultins)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 15))
			return ((*p[i])(v, cmd, params + 1));
		i++;
	}
	i = ft_execve(v, NULL, params);
	if (i < 0)
		return (0);
	else if (i)
		return (1);
	if (v->stdout_copy) // if stdout has been copied. so > must exist
		reset_fd(v); // protect
	ft_printf(CMD_NOTFOUND, v->__executable->content, params[0]);
	if (!sethistory(&v->history_head, v->line, "127"))
		return (0);
	return (1);
}

static int confirm_flags(t_vars *v, char ***argv, t_cmd *cmd, size_t splitsize)
{
	char	*line;
	char	*temp;
	t_cmd	*newcmd;
	int fd;

	if (cmd->type && !cmd->next)
	{
		if (cmd->type == PIPE)
		{
			ft_printf("pipe> ");
			get_next_line(STDIN_FILENO, &line);
			newcmd = cmd__ft_lstnew(line[findflag(line, FLAGS)], line);
			if (!newcmd)
			{
				free(line);
				return (-1);
			}
			cmd__ft_lstadd_back(&cmd, newcmd);
			temp = ft_strjoin(v->line, line);
			free(v->line);
			v->line = temp;
		}
		else if (cmd->type == ANGLEBRACKETLEFT || cmd->type == ANGLEBRACKETRIGHT)
		{
			ft_printf("%s: parse error near `\\n'\n", v->__executable->content);
		}
	}
	else if (cmd->type)
	{
		if (cmd->type == ANGLEBRACKETLEFT)
		{
			fd = open(cmd->next->line, O_RDONLY);
			if (fd < 0)
				ft_printf(DIR_NOTFOUND, v->__executable->content, cmd->next->line);
			else
				ft_printf("\x1B[32m'%s' exist!\n\x1B[0m", cmd->next->line);
			close(fd);
		}
		if (cmd->prev && cmd->prev->type == PIPE)
		{
			/*
			** 1. Malloc the array bigger by one.
			** 2. Move every argument further
			** 3. Put the output in the second.
			** 4. Run command normally.
			*/
			ft_printf("TYPE NOW = %c\n", PIPE);

			ft_split("splitsize = %d\n", splitsize);
		}
		if (cmd->type == ANGLEBRACKETRIGHT)
		{
			v->stdout_copy = dup(1);
			close(STDOUT_FILENO);
			v->fd = open(cmd->next->line, O_WRONLY | O_CREAT  | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		if (cmd->type == ANGLEBRACKETDOUBLERIGHT)
		{
			/*
			** 1. Read the file using ft_getline and store it.
			** 2. Delete the file.
			** 3. Print out the old file.
			** 4. Run command normally.
			*/
			ft_printf("TYPE NOW = %c\n", ANGLEBRACKETDOUBLERIGHT);
		}
	}
	return (1);
}


/*
** call this command.
**
*/
int run_cmd(t_vars *v, t_cmd *cmd)
{
	char	**args;
	size_t	splitsize;
	int ret;

	while (cmd) // loops through commands
	{
		args = ft_split_sep(cmd->line, " \t", &splitsize);
		ret = confirm_flags(v, &args, cmd, splitsize);
		if (ret == -1)
		{
			ft_free_array((void*)args, (int)splitsize);
			ft_exit_error(v, 1);
		}
		if (ret && !run_command(v, args, cmd))
		{
			ft_free_array((void*)args, (int)splitsize);
			ft_exit_error(v, 1);
		}
		if (v->stdout_copy) // if stdout has been copied. so > must exist
			reset_fd(v); // protect
		ft_free_array((void*)args, (int)splitsize);
		cmd = cmd->next;
		errno = 0;
	}
	return (1);
}

int ft_split_input(t_vars *v);

void	read_user_input(t_vars *v)
{
	t_node	*node;
	t_cmd	*command;
	int i;

	i = 0;
	ft_printf(v->prefix, v->__logname->content, ft_strrchr(v->current_path, '/') + 1);
	v->ret = get_next_line(STDIN_FILENO, &v->line);
	if (v->ret < 0)
		ft_exit_error(v, 1);
	if (*v->line != 0)
	{
		// system(ft_strjoin(v->line, "2")); // for comparing output
		if (!ft_split_input(v)) // sometimes random memory.
			ft_exit_error(v, 1);
		node= v->nodehead;
		while (node)
		{
			// command = node->cmd;
			// while (command)
			// {
			// 	ft_printf("\x1B[34mparse | %p - string = [%c][%s]\n\x1B[0m", command, command->type, command->line);
			// 	command = command->next;
			// }
			if (!run_cmd(v, node->cmd))
				ft_exit_error(v, 1);
			node = node->next;
		}
	}
	free(v->line);
}
// cd ..  | echo | pwd ; env < test.txt ; env
// cd ..  | echo | pwd ; env ; env
// export PATH=/Users/bdekonin/Documents/Projects/minishell/noperm
