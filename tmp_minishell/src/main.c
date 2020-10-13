/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 22:19:16 by lverdoes      ########   odam.nl         */
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
			return (run_pipe(v, args, first_cmd, tmp));
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

// // void	expand_tokens(t_vars *v, t_list *section_start)
// // {
// // 	t_list	*tmp;
// // 	t_list	*prv;
// // 	t_list *next;
// // 	char	*str;
// // 	// print_tokens(v, "");
// // 	tmp = section_start;

// // 	char *newString;
// // 	while (tmp && !is_semicolon(tmp->content))
// // 	{
// // 		if (!is_pipe(tmp->content) && !is_redirection(tmp->content))
// // 			expansion(v, (char **)&tmp->content);
// // 	// 	newString = NULL;
// // 		if (is_end(tmp->content))
// // 		{
// // 			tmp = tmp->next;
// // 			continue;
// // 		}
// // 		newString = tmp->content;
// // 		if (tmp)
// // 			tmp = tmp->next;
// // 		if (is_end(tmp->content))
// // 			continue;
// // 		while (tmp && !is_end(tmp->content))
// // 		{
// // 	// 		if (is_semicolon(tmp->content))
// // 	// 			return ;
// // 	// 		expansion(v, (char **)&tmp->content);
// // 	// 		resize_str(v, &newString, tmp->content);
// // 	// 		prv = tmp;
// // 			if (!tmp)
// // 				ft_printf("\033[0;31m1: [%s]\033[0m\n", "null");
// // 			else
// // 				ft_printf("\033[0;31m1: [%s]\033[0m\n", tmp->content);
// // 	// 		if (tmp)
// // 				tmp = tmp->next;
// // 	// 		ft_lst_remove_one(&v->cmd, prv);
// // 		}
// // 		if (!tmp)
// // 			ft_printf("\033[0;32m2: [%p]-[%s]\033[0m\n", section_start, "null");
// // 		else
// // 			ft_printf("\033[0;32m2: [%p]-[%s]\033[0m\n", section_start, tmp->content);
// // 	// 	// ft_printf("\033[0;32m2: [%p]-[%s]\033[0m\n", section_start, newString);
// // 		if (tmp)
// // 			tmp = tmp->next;
// // 	}
// // 	// print_tokens(v, "");
// // }

// Bob
// export a='hoi bob' ; echo $a ; export a='hoi lars' ; echo $a
//			ls -la | 'cat' -e ; pwd
// blabla:		ls -la | 'cat' -e | grep -R 'vaggginas' -O ; export a=pwd ; $LOGNAME ; echo -n -n -nnn hoi $USER ; echo en hallo "$SHELL" klaar 
void	expand_tokens(t_vars *v, t_list *section_start)
{
	t_list	*tmp;
	t_list	*prv;
	t_list *next;
	char	*str;
	// print_tokens(v, "");
	tmp = section_start;

	char *newString = tmp->content;
	while (tmp && !is_semicolon(tmp->content))
	{
		if (tmp->next && is_end(tmp->next->content))
			newString = tmp->next->next->content;
		else
		{
			while (tmp && !is_end(tmp->content))
			{
				resize_str(v, &newString, tmp->content);
				tmp = tmp->next;
			}
		}
		// newString = NULL;
		if (tmp)
			tmp = tmp->next;
	}
	printf("newString: %s\n", newString);
	// print_tokens(v, "");
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
//	print_tokens(v, "156");							//debug
	find_semicolons(v);
	i = 0;
	while (v->semicolon_ptrs[i] != NULL)
	{
		expand_tokens(v, v->semicolon_ptrs[i]);
		printf("\n---\n\n");
//		parse_input(v, v->semicolon_ptrs[i]);
		reset_std(v);


		
		i++;
	}
//	print_tokens(v, "168");							//debug
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
