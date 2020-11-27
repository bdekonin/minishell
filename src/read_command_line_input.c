/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_command_line_input.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 19:48:24 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/27 12:12:22 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_printerror(char *file, int error)
{
	ft_putstr_fd(MINISHELL, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (error == ENOENT)
		ft_putendl_fd(MINISHELL_ENOENT, 2);
	else if (error == EACCES)
		ft_putendl_fd(MINISHELL_EACCES, 2);
	else if (error == CMDERR)
		ft_putendl_fd(MINISHELL_CMDERR, 2);		
}

int	run_command(t_vars *v, char **params)
{
	int		(*p[7]) (t_vars *v, char **params);
	size_t	i;
	int		ret;
	
	p[0] = ft_echo;
	p[1] = ft_cd;
	p[2] = ft_pwd;
	p[3] = ft_export;
	p[4] = ft_unset;
	p[5] = ft_env;
	p[6] = ft_exit;
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 16))
				return ((*p[i])(v, params + 1));
		i++;
	}
	ret = ft_execve(v, params);
	if (ret == FILENOTFOUND * 10)
		ft_printerror(params[0], CMDERR);
	if (ret == FILENOTFOUND * 10)
		return (ret / 10);
	return (ret);
}

void		split_tokens(t_vars *v, char *string)
{
	char	**tokens;
	size_t	size_tokens;

	if (string[0] == 0)
	{
		v->cmd_ret = 1;
		return ;
	}
	tokens = ft_split_multi(string, "*", &size_tokens);
	malloc_check(v, tokens);
	v->cmd_ret = run_command(v, tokens);
	ft_free_array((void **)tokens, size_tokens);
}

int pipe_handler(t_vars *v, t_cmd *temp);

int		execute_loop(t_vars *v, t_cmd *list)
{
	int ret;

	signal(SIGQUIT, signal_execve);
	signal(SIGINT, signal_execve);
	while (list)
	{
		ret = 0;
		ret = redirection_handler(v, list);
		if (ret == 0)
			break;
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
	signal(SIGQUIT, signal_default);
	signal(SIGINT, signal_default);
	return (1);
}

int	read_command_line_input(t_vars *v, char *cli)
{
	size_t	i;
	char	**args;
	size_t	splitsize;
	int ret;

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
		ret = execute_loop(v, v->cmd);
		cmd__ft_lstclear(&v->cmd, free);
		if (ret == 0)
			break;
		i++;
	}
	ft_free_array((void**)args, splitsize);
	return (1);
}

void control_d(t_vars *v, char **cli, int ret)
{
	char *tmp;

	if (!*cli[0])
		ft_exit_error(v, EXIT_SUCCESS, 1);
	tmp = ft_strdup(*cli);
	free(*cli);
	malloc_check(v, tmp);
	while (ret == 0)
	{
		*cli = NULL;
		ret = get_next_line(STDIN_FILENO, cli);
		if (ret < 0)
			ft_exit_error(v, EXIT_FAILURE, 0);
		tmp = ft_append(tmp, (*cli));
		free(*cli);
		malloc_check(v, tmp);
	}
	*cli = tmp;
}