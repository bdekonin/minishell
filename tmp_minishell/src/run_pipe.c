/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:38:28 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 13:03:41 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pipe(t_vars *v, t_list *first_cmd, t_list *flag)
{
	char *arg;

	pipe(v->pipefd);
	v->forky = fork();
	if (v->forky == 0)
	{
		close(v->pipefd[0]);
		v->stdout_copy = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(v->pipefd[1], STDOUT_FILENO);
		arg = first_cmd->content;
		expansion(v, &arg);
		split_tokens(v, &arg);
		close(v->pipefd[1]);
		exit(1);
	}
	else
	{
		close(v->pipefd[1]);
		v->stdin_copy = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup2(v->pipefd[0], STDIN_FILENO);
		arg = flag->next->content;
		expansion(v, &arg);
		split_tokens(v, &arg);
		close(v->pipefd[0]);
		wait(NULL);
	}
	return (1);
}