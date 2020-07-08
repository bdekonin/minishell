/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_run_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/08 09:18:17 by bdekonin      ########   odam.nl         */
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
	if (cmd->prev && cmd->type != RDIRLEFT)
		return (1);
	int i;
	int (*p[8]) (t_vars *v, t_cmd *cmd, char **params, char **ret);

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
			return ((*p[i])(v, cmd, params + 1, ret));
		i++;
	}
	i = ft_execve(v, NULL, params, ret);
	// if (!i)
	// 	return (0);
	// else if (i)
	// 	return (1);
	ft_printf(CMD_NOTFOUND, v->__executable + 2, params[0]);
	*ret = ft_strdup("0"); // maybe 1?
	if (!*ret)
		return (0);
	return (1);
}

static int confirm_flags(t_vars *v, t_cmd *cmd)
{
	char	*line;
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
				return (0);
			}
			cmd__ft_lstadd_back(&cmd, newcmd);
		}
		else if (cmd->type == RDIRLEFT || cmd->type == RDIRRIGHT)
		{
			ft_printf("%s: parse error near `\\n'\n", v->__executable + 2);
		}
	}
	else if (cmd->type)
	{
		if (cmd->type == RDIRLEFT)
		{
			fd = open(cmd->next->line, O_RDONLY);
			if (fd < 0)
				ft_printf(DIR_NOTFOUND, v->__executable + 2, cmd->next->line);
			else
				ft_printf("\x1B[32m'%s' exist!\n\x1B[0m", cmd->next->line);
		}
		// if (cmd->type == RDIRRIGHT)
		// {
		// 	int stat;
			// pid_t forky;

		// 	forky = fork();
		// 	if (!forky)
		// 	{
		// 		int fd = open(cmd->next->line, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); // check things
		// 		dup2(fd, 1);
		// 		close(fd);
		// 	}
		// 	// else if (forky > 0)
		// 		// wait(&stat);
		// }
	}
	return (1);
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

	while (cmd) // loops through commands
	{
		args = ft_split_sep(cmd->line, " \t", &splitsize);
		if (!confirm_flags(v, cmd) || !run_command(v, args, cmd, &ret))
		{
			ft_free_array((void*)args, (int)splitsize);
			free(ret);
			ft_exit_error(v, 1);
		}
		if (cmd->type != RDIRLEFT)
		{
			if (!sethistory(&v->history_head, v->line, ret, cmd->line))
			{
				ft_free_array((void*)args, (int)splitsize);
				free(ret);
				ft_exit_error(v, 1);
			}
		}
		ft_free_array((void*)args, (int)splitsize);
		cmd = cmd->next;
	}
	return (1);
}

int ft_split_input(t_vars *v);

void	read_user_input(t_vars *v)
{
	int i;

	i = 0;
	ft_printf(v->prefix, v->__logname->content, ft_strrchr(v->current_path, '/') + 1);
	v->ret = get_next_line(STDIN_FILENO, &v->line);
	if (v->ret < 0)
		ft_exit_error(v, 1);
	if (*v->line != 0)
	{
		if (!ft_split_input(v)) // sometimes random memory.
			ft_exit_error(v, 1);
		while (v->cmdlist[i])
		{
			if (!run_cmd(v, v->cmdlist[i]))
				ft_exit_error(v, 1);
			i++;
		}
	}
	free(v->line);
}
// cd ..  | echo | pwd ; env < test.txt ; env
