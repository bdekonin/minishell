/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:38:28 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/27 13:42:43 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_list *lastpipe(t_list *headptr);
int pipe_next(t_vars *v, t_list *list, int *oldPipe, int first, int *opper_fd);

static size_t pipecounter(t_list *list)
{
	size_t counter;

	counter = 0;
	while (list)
	{
		if (is_pipe(list->content))
			counter++;
		else if (is_end(list->content))
			return (counter);
		list = list->next;
	}
	return (counter);
}

int pipe_handler(t_vars *v, t_list *temp)
{
	int stdfd[2];
	stdfd[1] = STDIN_FILENO;

	int opper_fd[2]; 
	if (pipe(opper_fd) < 0)
			exit(EXIT_FAILURE);
	
	ft_printf("pipecount = %d\n", pipecounter(temp));

	pipe_next(v, temp, NULL, 1, opper_fd);
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
			
			system(list->content);
			dprintf(v->stdout_copy, "run\n");
			exit(EXIT_SUCCESS);
		}
		else if (v->forky > 0) // Parent
		{
			// Parent
			wait(NULL);
		}
		else // Error
			ft_exit_error(v, EXIT_FAILURE);
		pipe_next(v, list->next->next, newPipe, 0, opper_fd);
		close(newPipe[0]);
		close(newPipe[1]);
	}
	else
	{
		close(opper_fd[1]);
		dup2(opper_fd[0], STDIN_FILENO);
		system(list->content);
	}
	close(opper_fd[0]);
	close(opper_fd[1]);
	return (1);
}
