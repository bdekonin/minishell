/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_run_command.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/19 23:48:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/08/04 12:51:57 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline int reset_stdin(t_vars *v)
{
	dup2(v->stdin_copy, 0);
	close(v->stdin_copy);
	v->stdin_copy = 0;
	return (1);
}

static inline int reset_stdout(t_vars *v)
{
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
	cmd_str[8] = "history";
	cmd_str[9] = NULL;
	return (cmd_str[i]);
}
// pwd | cat > output 
int run_command(t_vars *v, char **params, t_cmd *cmd, size_t *splitsize)
{
	if (cmd->prev && (cmd->prev->type == ANGLEBRACKETLEFT || cmd->prev->type == ANGLEBRACKETRIGHT || cmd->prev->type == ANGLEBRACKETDOUBLERIGHT))
		return (1);
	int i;
	int (*p[bultins]) (t_vars *v, t_cmd *cmd, char **params);

	i = 0;
	p[0] = echo;
	p[1] = cd;
	p[2] = pwd;
	p[3] = exportt;
	p[4] = unset;
	p[5] = env;
	p[6] = ft_exit;
	p[7] = debug;
	p[8] = ft_history;
	ft_str_tolower(params[0]);
	while (i < bultins)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 15))
			return ((*p[i])(v, cmd, params + 1));
		i++;
	}
	i = ft_execve(v, cmd, params, splitsize);
	if (i < 0)
		return (0);
	else if (i)
		return (1);
	if (v->stdout_copy) // if stdout has been copied. so > must exist
		reset_stdout(v); // protect
	ft_printf(CMD_NOTFOUND, v->__executable->content, params[0][0]);
	if (!sethistory(&v->history_head, v->line, "127"))
		return (0);
	return (1);
}
int confirm_flags(t_vars *v, char ***argv, t_cmd *cmd, size_t splitsize);

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
		//printf("cmdline=[%s]\n", cmd->line);
		args = ft_split_sep_exep(cmd->line, "*", &splitsize);
		//args = ft_split_sep_exep(cmd->line, " /t", &splitsize);
		ret = confirm_flags(v, &args, cmd, splitsize);
		if (ret == -1)
		{
			ft_free_array((void*)args, (int)splitsize);
			ft_exit_error(v, 1);
		}
		if (ret && !run_command(v, args, cmd, &splitsize))
		{
			ft_free_array((void*)args, (int)splitsize);
			ft_exit_error(v, 1);
		}
		// if ((cmd->type == PIPE || (cmd->prev && cmd->prev->type == PIPE)) && v->forky == 0) // maybe prev->type == PIPE
		if (v->stdout_copy) // if stdout has been copied. so > must exist
			reset_stdout(v); // protect
		if (v->stdin_copy) // if stdin has been copied. so > must exist
			reset_stdin(v); // protect
		ft_free_array((void*)args, (int)splitsize);
		cmd = cmd->next;
		errno = 0;
	}
	return (1);
}

int ft_split_input(t_vars *v);
char *print_strings2(t_vars *v, char *str, char *command);

void	read_user_input(t_vars *v)
{
	t_node	*node;
	int i;

	i = 0;
	// ft_printf("%d | ", getpid());
	ft_printf(v->prefix, v->__logname->content, ft_strrchr(v->current_path, '/') + 1);
	v->ret = get_next_line(STDIN_FILENO, &v->line);
	if (v->ret < 0)
		ft_exit_error(v, 1);

	// v->line = ft_strdup("cat main.c | cat -e");
	if (*v->line != 0)
	{
		if (!ft_split_input(v)) // sometimes random memory.
			ft_exit_error(v, 1);
		node= v->nodehead;
		while (node)
		{
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
