/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/28 15:04:39 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_command(t_vars *v, char **params)
{
	int		(*p[BUILTINS]) (t_vars *v, char **params);
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
	while (i < BUILTINS)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 16))
				return ((*p[i])(v, params + 1));
		i++;
	}
//	ft_print_array(params);						//debug
	ret = ft_execve(v, params);
//	printf("ret = [%d]\n", ret);				//debug
	if (!ret)
		ft_printf(CMD_NOTFOUND, "minishell", params[0]);
	return (ret);
}

void		split_tokens(t_vars *v, char *string)
{
	char	**tokens;
	size_t	size_tokens;

	tokens = ft_split_multi(string, "*", &size_tokens);
	if (!tokens)
		ft_exit_error(v, EXIT_FAILURE);
	v->cmd_ret = run_command(v, tokens);
	ft_free_array((void **)tokens, size_tokens);
}

int pipe_handler(t_vars *v, t_list *temp);
t_list *lastpipe(t_list *headptr)
{
	t_list *last;

	last = headptr;
	while (headptr)
	{
		if (is_pipe(headptr->content))
			last = headptr;
		headptr = headptr->next;
	}
	return (last->next);
}

int		execute_loop(t_vars *v, t_list *list)
{
	t_list *temp;

	while (list)
	{
		if (list->next && is_pipe(list->next->content))
		{
			pipe_handler(v, list);
			list = lastpipe(list);
		}
		else
			split_tokens(v, list->content);
		list = list->next;
	}
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

		for (t_list *list = v->cmd; list; list = list->next)
		{
			if (!is_pipe(list->content) && !is_redirection(list->content))
				expansion(v, (char**)&list->content);
		}
		execute_loop(v, v->cmd);
		ft_lstclear(&v->cmd, free);
		free(args[i]);
		i++;
	}
	free(args);
	ft_lstclear(&v->cmd, free);
	return (ft_free(v->semicolon_ptrs));
}

void		signal_handler(int sig)
{
	ft_putendl_fd("\b\b  ", 1);
//	ft_putstr_fd("\b\b", 1);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
}

int 		main(int argc, char **argv, char **envp)
{
	t_vars v;
	char *cli;

	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	initialize(&v, envp);
	while (1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		if (get_next_line(STDIN_FILENO, &cli) < 0)
			ft_exit_error(&v, EXIT_FAILURE);
		read_command_line_input(&v, cli);
	}
	return (0);
}
