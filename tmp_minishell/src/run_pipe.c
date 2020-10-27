/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:38:28 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/27 19:56:08 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tester = 0;


t_list *lastpipe(t_list *headptr);
int pipe_next(t_vars *v, t_list *list, int *oldPipe, int first, int *opper_fd);

static void savefd(t_vars *v)
{
	v->stdin_copy = dup(STDIN_FILENO);
	v->stdout_copy = dup(STDOUT_FILENO);
}

int pipe_handler(t_vars *v, t_list *temp)
{
	savefd(v);
	if (tester == 0)
		tester = dup(STDOUT_FILENO);

	int stdfd[2];
	stdfd[1] = STDIN_FILENO;

	int opper_fd[2]; 
	if (pipe(opper_fd) < 0)
			exit(EXIT_FAILURE);

	pipe_next(v, temp, NULL, 1, opper_fd);
	reset_std(v);

	dprintf(tester, "here [%d]\n", getpid());
	// ft_putendl_fd("\b\b ", STDOUT_FILENO);
	// ft_putstr_fd(PROMPT, STDOUT_FILENO);
	return (1);
}

// pwd | wc | cat -e
int pipe_next(t_vars *v, t_list *list, int *oldPipe, int first, int *opper_fd)
{
	int newPipe[2];

	if (list->next && is_pipe(list->next->content))
	{
		if (pipe(newPipe) < 0)
			ft_exit_error(v, EXIT_FAILURE);
		v->forky = fork();
		if (first == 0)
		{
			close(oldPipe[1]);
			dup2(oldPipe[0], STDIN_FILENO);
		}
		if (v->forky == 0) // Child
		{
			int test = -1;
			if (list->next->next == lastpipe(list))
            {
				close(opper_fd[0]);
				close(STDOUT_FILENO);
				dup2(opper_fd[1], STDOUT_FILENO);
				test = 1;
            }
			else
			{
				close(newPipe[0]);
				close(STDOUT_FILENO);
				dup2(newPipe[1], STDOUT_FILENO);
				test = 0;
			}
			
			// system(list->content);
			split_tokens(v, list->content);
			// dprintf(v->stdout_copy, "run\n");
			exit(EXIT_SUCCESS);
		}
		else if (v->forky > 0) // Parent
		{
			// Parent
			// wait(NULL);
		}
		else // Error
			ft_exit_error(v, EXIT_FAILURE);
		pipe_next(v, list->next->next, newPipe, 0, opper_fd);
		close(newPipe[0]);
		close(newPipe[1]);
		if (first == 0)
			return (1);
	}
	else
	{
		close(opper_fd[1]);
		dup2(opper_fd[0], STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(v->stdout_copy, STDOUT_FILENO);
		// system(list->content);
		split_tokens(v, list->content);
	}
	close(opper_fd[0]);
	close(opper_fd[1]);
	return (1);
}
