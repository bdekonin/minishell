/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/14 14:38:51 by bdekonin      ########   odam.nl         */
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
	ft_free_array((void **)tokens, size_tokens);
}

int		parse_input(t_vars *v, t_list *first_cmd)
{
	// while (tmp)
	// {
		
	// }
	char *temp = ft_strdup(first_cmd->content);
	ft_printf("first_cmd: %s\n", temp);
	split_tokens(v, &temp);
	return (1);
}

// Bob
// export a='hoi bob' ; echo $a ; export a='hoi lars' ; echo $a
// blabla:		ls -la | 'cat' -e | grep -R 'vaggginas' -O ; export a=pwd ; $LOGNAME ; echo -n -n -nnn hoi $USER ; echo en hallo "$ SHELL" klaar 

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
		
		parse_input(v, v->cmd);
		reset_std(v);
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
	//signals
	while (1)
	{
		print_prefix(&v);
		if (get_next_line(STDIN_FILENO, &cli) < 0)
			ft_exit_error(&v, EXIT_FAILURE);
		read_command_line_input(&v, cli);
	}
	return (0);
}
