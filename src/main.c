/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/14 00:39:29 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_printerror(char *file, int error)
{
	ft_putstr_fd(MINISHELL, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (error == ENOENT)
		ft_putendl_fd(MINISHELL_ENOENT, STDERR_FILENO);
	else if (error == EACCES)
		ft_putendl_fd(MINISHELL_EACCES, STDERR_FILENO);
	else if (error == CMDERR)
		ft_putendl_fd(MINISHELL_CMDERR, STDERR_FILENO);		
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
	ft_str_to_lower(*params);
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

	tokens = ft_split_multi(string, "*", &size_tokens);
	if (!tokens)
		ft_exit_error(v, EXIT_FAILURE, 1);
	v->cmd_ret = run_command(v, tokens);
	ft_free_array((void **)tokens, size_tokens);
	reset_std(v);
}

int pipe_handler(t_vars *v, t_cmd *temp);

// ls > output.txt src libft | wc > tester
// pwd > output
// cat | cat -e > output
// ls > output.txt src libft | wc > tester
// [> output]
// [echo hoi > file1 hallo > file2 welkom]

int		execute_loop(t_vars *v, t_cmd *list)
{
	int ret;

	signal(SIGQUIT, signal_execve);
	signal(SIGINT, signal_execve);
	while (list)
	{
		// if (lastpipe(list))
		// 	ft_printf("---[%s] - [%c]\n", lastpipe(list)->line, lastpipe(list)->type);
		if (redirection_handler(v, list) == 0)
			break;
		if (list->type == PIPELINE)
		{
			pipe_handler(v, list);
			list = lastpipe(list);
		}
		else if (!list->prev || list->prev->type == 0)
			split_tokens(v, list->line);
		list = list->next;
	}
	signal(SIGQUIT, signal_default);
	signal(SIGINT, signal_default);
	return (1);
}

static int	read_command_line_input(t_vars *v, char *cli)
{
	size_t	i;
	char **args;

	if (!syntax_error_check(v, cli))
		return (ft_free(cli));
	size_t splitsize = 0;
	args = ft_split_multi(cli, ";", &splitsize);
	free(cli);
	i = 0;
	while (i < splitsize)
	{
		create_tokens(v, args[i]);
		for (t_cmd *test = v->cmd; test; test = test->next)
			expansion(v, &(test->line));
		execute_loop(v, v->cmd);

		cmd__ft_lstclear(&v->cmd, free);
		i++;
	}
	ft_free_array((void**)args, splitsize);
	cmd__ft_lstclear(&v->cmd, free);
	return (1);
}

int 		main(int argc, char **argv, char **envp)
{
	t_vars v;
	char *cli;

	initialize(&v, envp);
	while (1)
	{
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		if (get_next_line(STDIN_FILENO, &cli) < 0)
			ft_exit_error(&v, EXIT_FAILURE, 0);
		read_command_line_input(&v, cli);
	}
	return (0);
}
