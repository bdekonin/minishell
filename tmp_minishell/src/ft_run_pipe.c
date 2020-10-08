/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run_pipe.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/30 12:29:10 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/08 15:35:44 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pipe(t_vars *v, t_list *tmp)
{
	t_cmd *node;
	t_cmd *cmd_node;
	t_list *cmd1;
	char *arg;

	node = tmp->next->content;
	pipe(v->pipefd);
	v->forky = fork();
	if (v->forky == 0)
	{
		close(v->pipefd[0]);
		v->stdout_copy = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(v->pipefd[1], STDOUT_FILENO);
		cmd1 = get_prev_node(v, tmp); 			//dont get prev, get first!
		cmd_node = cmd1->content;
		arg = cmd_node->token;
		expansions(v, &arg);
		split_tokens(v, &arg);					//check ret?
		close(v->pipefd[1]);
		exit(1);
	}
	else
	{
		close(v->pipefd[1]);
		v->stdin_copy = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(v->pipefd[0], STDIN_FILENO);
		system("wc");
		close(v->pipefd[0]);
		wait(NULL);
	}
	return (1);
}