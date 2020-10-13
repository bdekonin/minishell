/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 13:24:32 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_execve(t_vars *v, char **params)
{
	int		ret;
	char	*new_path;
	char	**envp;
	pid_t	spoon;
	int		stat;
	
	new_path = NULL;
	if (!ft_strncmp(params[0], "./", 2))
	{
		ret = get_relative_path(v, &new_path, params);
		//printf("get_relative_path ret = [%d]-[%s]\n", ret, new_path); 	//debug
		if (ret < 0)
		{
			ft_printf("%s: %s: %s\n", v->default_executable->content, params[0], strerror(errno));
			return (ret);
		}
	}
	else
	{	
		ret = loop_locations(v, &new_path, params);
		if (ret == -1 || ret == 0)
			return (ret);
	}
	envp = env_list_to_array(v);
	if (!envp)
		return (-1);
	spoon = fork();
	if (!spoon)
	{
//		signal(SIGINT, SIG_DFL); // ctrl c - for cat so you can quit
//		signal(SIGTSTP, SIG_DFL); // ctrl z
		//printf("params=[%s]\n", params[0]);		//debug
		//printf("path=[%s]\n", new_path);			//debug
		if (execve(new_path, &params[0], envp) < 0)
		{
			ft_printf("%s: %s\n", v->default_executable->content, strerror(errno));
			exit(COMMAND_NOT_RUNNABLE);
		}
	}
	else
	{
		wait(&stat);
	}
	ft_free_array((void **)envp, ft_lstsize(v->env));
	free(new_path);
	//set_history(v);
	return (1);
}

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
		ft_printf(CMD_NOTFOUND, v->default_executable->content, params[0]);
	return (ret);
}

void		split_tokens(t_vars *v, char **args)
{
	char	**tokens;
	size_t	size_tokens;
	
	tokens = ft_split_multi(*args, "*", &size_tokens);
	free(*args);
	if (!tokens && v->cmd)
		ft_exit_error(v, EXIT_FAILURE);
	if (tokens)
		v->cmd_ret = run_command(v, tokens);
//	printf("cmd_ret = [%d]\n", v->cmd_ret);				//debug
	ft_free_array((void **)tokens, size_tokens);
}

int		parse_input(t_vars *v, t_list *first_cmd)
{
	t_list	*tmp;
	char	*args;
	
	tmp = first_cmd;
	args = NULL;
	while (tmp)
	{
		if (is_semicolon(tmp->content))
			break ;
		if (is_pipe(tmp->content))
		{
			return (run_pipe(v, first_cmd, tmp));
		}
		if (is_redirection(tmp->content))
		{
			
			if (!run_redirection(v, first_cmd, tmp))
				return (ft_free(args));
			break ;
		}
		expansion(v, (char **)&((tmp->content)));
		resize_str(v, &args, tmp->content);
		tmp = tmp->next;
	}
	if (args)
		split_tokens(v, &args);
	return (1);
}	

static int	read_command_line_input(t_vars *v)
{
	char	*cli;
	int		gnl_ret;
	size_t	i;
	
	gnl_ret = get_next_line(STDIN_FILENO, &cli);
	if (gnl_ret < 0)
		ft_exit_error(v, EXIT_FAILURE);
	if (!syntax_error_check(v, cli))
		return (ft_free(cli));
	create_tokens(v, cli);
	free(cli);
//	print_tokens(v);							//debug
	find_semicolons(v);
	i = 0;
	while (v->semicolon_ptrs[i] != NULL)
	{
		parse_input(v, v->semicolon_ptrs[i]);
		reset_std(v);


		
		i++;
	}
	ft_lstclear(&v->cmd, free);
	return (ft_free(v->semicolon_ptrs));
}

int 		main(int argc, char **argv, char **envp)
{
	t_vars v;

	initialize(&v, envp);
	//signals
	while (1)
	{
		print_prefix(&v);
		read_command_line_input(&v);
	}
	return (0);
}
