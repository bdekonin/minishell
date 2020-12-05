/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_command_line_input.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 19:48:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/12/05 16:28:59 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				run_command(t_vars *v, char **params, size_t i)
{
	int		(*p[7]) (t_vars *v, char **params);
	int		ret;

	p[0] = ft_echo;
	p[1] = ft_cd;
	p[2] = ft_pwd;
	p[3] = ft_export;
	p[4] = ft_unset;
	p[5] = ft_env;
	p[6] = ft_exit;
	while (i < 7)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 16))
			return ((*p[i])(v, params + 1));
		i++;
	}
	ret = \
	ft_execve(v, params, NULL, make_backup_command(v, ft_strdup(params[0])));
	free(v->backup_command);
	if (ret == FILENOTFOUND * 10)
		ft_printerror(params[0], CMDERR);
	if (ret == FILENOTFOUND * 10)
		return (ret / 10);
	return (ret);
}

static int		execute_loop(t_vars *v, t_cmd *list, int ret)
{
	while (list)
	{
		ret = 0;
		ret = redirection_handler(v, list);
		if (ret == 0)
			break ;
		else if (ret == 2)
		{
			list = v->cmd;
			continue;
		}
		if (list->type == PIPELINE)
		{
			pipe_handler(v, list);
			list = lastpipe(list);
		}
		else if (!list->prev || list->prev->type == 0)
			split_tokens(v, list->line);
		reset_std(v);
		if (!ft_strncmp("exit", list->line, 4) && v->cmd_ret == 1)
			return (0);
		list = list->next;
	}
	return (1);
}

static int		that_loop_tho(t_vars *v)
{
	int ret;

	signal(SIGQUIT, signal_execve);
	signal(SIGINT, signal_execve);
	ret = execute_loop(v, v->cmd, 0);
	signal(SIGQUIT, signal_default);
	signal(SIGINT, signal_default);
	return (ret);
}

int				read_command_line_input(t_vars *v, char *cli)
{
	size_t	i;
	char	**args;
	size_t	splitsize;
	int		ret;

	if (!initial_syntax_error_check(v, cli))
		return (0);
	splitsize = 0;
	args = ft_split_sep_exep(cli, ";", &splitsize);
	malloc_check(v, args);
	if (!syntax_error_check_loop(v, args, splitsize))
		return (ft_free_array((void**)args, splitsize));
	i = 0;
	while (i < splitsize)
	{
		create_tokens(v, args[i]);
		changestruct(v, v->cmd);
		expansion(v);
		ret = that_loop_tho(v);
		cmd__ft_lstclear(&v->cmd, free);
		if (ret == 0)
			break ;
		i++;
	}
	return (free_input_args((void**)args, splitsize));
}
