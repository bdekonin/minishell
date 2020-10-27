/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/27 11:42:46 by bdekonin      ########   odam.nl         */
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

void		split_tokens(t_vars *v, char *args)
{
	char	**tokens;
	size_t	size_tokens;

	tokens = ft_split_multi(args, "*", &size_tokens);
	if (!tokens)
		ft_exit_error(v, EXIT_FAILURE);
	v->cmd_ret = run_command(v, tokens);
	ft_free_array((void **)tokens, size_tokens);
}


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

// ls | pwd | cat
int		execute_loop(t_vars *v, t_list *list)
{
	t_list *temp;

	while (list)
	{
		if (list && list->next && is_pipe(list->next->content))
		{
			while (list && list->next && is_pipe(list->next->content))
			{
				// Check command ( Make sure is exist before forking)
				ft_printf("\033[0;32m%s: pipe\033[0m\n", list->content);
				ft_printf("\033[0;36m2				Executing %s\033[0m\n", list->content);
				list = list->next;				
			}
		}
		// else if (list && list->next && is_redirection(list->next->content))
		// {
		// 	if (get_prev_node(v, list) && is_pipe(get_prev_node(v, list)->content))
		// 	{
		// 		ft_printf("\033[0;31m%s: PREV PIPE\033[0m\n", list->content);
		// 	}
		// 	else
		// 		ft_printf("\033[0;31m%s: REDIRRR\033[0m\n", list->content);
		// 	list = list->next;
		// }
		else
		{
			if (list == lastpipe(v->cmd)) // LAST PIPE RESET FD
			{	
				ft_printf("\033[0;33m%s: last   pipe\033[0m\n", list->content);
			}
			else
				ft_printf("\033[0;35m%s: aint a pipe\033[0m\n", list->content);
			ft_printf("\033[0;36m1				Executing %s\033[0m\n", list->content);
		}
		
		list = list->next;
	}
	
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
		execute_loop(v, v->cmd);
		reset_std(v);
		ft_lstclear(&v->cmd, free);
		free(args[i]);
		i++;
	}
	free(args);
	ft_lstclear(&v->cmd, free);
	return (ft_free(v->semicolon_ptrs));
}

int	run_pipe(t_vars *v, char *childCommand, char *parentCommand, int *fd);

int first_pipe(t_vars *v, t_list *list);
int pipe_next(t_vars *v, t_list *list, int *oldPipe, int first, int *opper_fd);
int 		main(int argc, char **argv, char **envp)
{
	t_vars v;
	char *cli;

	initialize(&v, envp);
	//signals

	 ft_printf("[%d] - PID\n", getpid());

		ft_printf("-----------------------------------------------------------------------------\n");
	
// echo hoi hoi hoi daar bob hoe is het | grep hoi | wc | wc | cat -e
	
		t_list *list = ft_lstnew(ft_strdup("echo hoi hoi hoi daar bob hoe is het"));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("|")));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("grep hoi")));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("|")));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("wc")));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("|")));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup("cat -e")));

		

	// // first_pipe(&v, list);

	// // pwd$
	v.stdin_copy = dup(STDIN_FILENO);
	v.stdout_copy = dup(STDOUT_FILENO);
	
	int fd[2];
	fd[1] = STDIN_FILENO;
	int opper_fd[2]; 
	if (pipe(opper_fd) < 0)
			exit(EXIT_FAILURE);
	pipe_next(&v, list, fd, 1, opper_fd);

	




 





	
	ft_printf("\n-----------------------------------------------------------------------------\n[%d] - Finisho\n", getpid());
	return (0);


		
	while (1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		if (get_next_line(STDIN_FILENO, &cli) < 0)
			ft_exit_error(&v, EXIT_FAILURE);
		read_command_line_input(&v, cli);
	}
	return (0);
}
