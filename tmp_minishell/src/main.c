/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 10:35:22 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/10/04 18:06:42 by lverdoes      ########   odam.nl         */
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

char		*cmd_str(int i)
{
	char	*cmd_str[BUILTINS + 1];

	cmd_str[0] = "echo";
	cmd_str[1] = "cd";
	cmd_str[2] = "pwd";
	cmd_str[3] = "export";
	cmd_str[4] = "unset";
	cmd_str[5] = "env";
	cmd_str[6] = "exit";
//	cmd_str[7] = "debug";
//	cmd_str[8] = "history";
//	cmd_str[9] = NULL;
	return (cmd_str[i]);
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
//	p[7] = ft_debug;
//	p[8] = ft_history;
	ft_str_to_lower(*params);
	i = 0;
	while (i < 7)			//change to: (i < BUILTINS)
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

int		split_tokens(t_vars *v, char **args)
{
	char	**tokens;
	size_t	size_tokens;
	
	tokens = ft_split_multi(*args, "*", &size_tokens);
	ft_free(*args);
	if (!tokens && v->cmd)
		ft_exit_error(v, EXIT_FAILURE);
	if (tokens)
		v->cmd_ret = run_command(v, tokens);
//	printf("cmd_ret = [%d]\n", v->cmd_ret);				//debug
	ft_free_array((void **)tokens, size_tokens);
	return (1);
}

int		split_input(t_vars *v, t_list *tmp, t_cmd *node)
{
	char 	*args;
	
	args = NULL;
	while (tmp)
	{
		node = tmp->content;
		if (is_semicolon(node->token))
			break ;
		if (is_pipe(node->token))
		{
			return (run_pipe(v, tmp));
		}
		if (is_redirection(tmp))
		{
			if (!run_flags_command(v, tmp))
				return (ft_free(args));
			break ;
		}
		if (!expansions(v, &node->token))
			return (ft_free(args)); //exit?
		if (!resize_str(&args, node->token))
			ft_exit_error(v, EXIT_FAILURE);
		tmp = tmp->next;
	}
//	printf("args=[%s]\n", args); 							//debug
	if (args)
		split_tokens(v, &args);								//check ret?
	return (1);
}

int		loop_input(t_vars *v)
{
	size_t i;

	i = 0;
	while (v->cmd_ptr[i] != NULL)
	{
//		t_cmd *temp = v->cmd_ptr[i]->content;		//debug
//		printf("next cmd: [%s]\n", temp->token);	//debug
		if (!split_input(v, v->cmd_ptr[i], NULL))
		{
			reset_std(v);
//			free_cmd_list(v);
//			ft_free(v->cmd_ptr);
			return (0);
		}
		reset_std(v);
		i++;
	}
	return (1);
}
	
int		read_user_input(t_vars *v)
{
	char	*cli;		//command line input
	int		gnl_ret;
	
	gnl_ret = get_next_line(STDIN_FILENO, &cli);
	if (gnl_ret < 0)
		ft_exit_error(v, EXIT_FAILURE);
	if (!syntax_error_check(v, cli))
		return (ft_free(cli));
	create_tokens(v, cli);
	ft_free(cli);
 //	print_tokens(v); 			//debug
	find_cmd_flags(v);
	loop_input(v);
	free_cmd_list(v);
	ft_free(v->cmd_ptr);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	t_vars v;
	
	//ft_printf("---- Starting ----\n----- %d -----\n\n", getpid()); //debug
	initialize_struct(&v, envp);
//	signal(SIGINT, SIG_IGN); // ctrl c
//	signal(SIGTSTP, SIG_IGN); // ctrl z
	while (1)
	{
		print_prefix(&v);
		read_user_input(&v);
	}
	return (1);
}
