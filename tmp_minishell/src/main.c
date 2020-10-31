/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/31 17:44:08 by bdekonin      ########   odam.nl         */
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
		ft_exit_error(v, EXIT_FAILURE);
	v->cmd_ret = run_command(v, tokens);
	ft_free_array((void **)tokens, size_tokens);
	reset_std(v);
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
	t_list		*temp;

	signal(SIGQUIT, signal_execve);
	signal(SIGINT, signal_execve);
	while (list)
	{
		redirection_handler(v, list);
		// if (list->next && is_pipe(list->next->content))
		// {
		// 	pipe_handler(v, list); // pipe returnvalues
		// 	list = lastpipe(list);
		// }
		// else
		// 	split_tokens(v, list->content);
		// ft_printf("token[%s]\n", list->content);
		list = list->next;
		// reset_std(v);
	}
	signal(SIGQUIT, signal_default);
	signal(SIGINT, signal_default);
	return (1);
}


// pwd > output
// ls > output.txt src libft | wc
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

int 		main(int argc, char **argv, char **envp)
{
	t_vars v;
	char *cli;

	initialize(&v, envp);
	while (1)
	{
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		if (get_next_line(STDIN_FILENO, &cli) < 0)
			ft_exit_error(&v, EXIT_FAILURE);
		read_command_line_input(&v, cli);
	}
	return (0);
}
