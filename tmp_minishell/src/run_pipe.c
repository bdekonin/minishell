/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:38:28 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/29 00:12:04249 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int piper(t_vars *v, t_list *list);
int       pipe_stuff(t_vars *v, t_list *list);


int pipe_handler(t_vars *v, t_list *temp)
{
	int opper_fd[2];

	pid_t forky = fork();
	if (!forky)
	{
		pipe_stuff(v, temp);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(forky, NULL, 0);
	// if (forky == 0)
		// exit(EXIT_SUCCESS);
	return (1);
}


// START
static void parent(t_vars *v, t_list *list, int *fd)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		exit(EXIT_FAILURE);
	}
	close(fd[1]);

	if (!is_now_or_prev(v, list))
		split_tokens(v, list->content);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

static void child(t_vars *v, t_list *list, int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[0]);
	if (list->next && is_pipe(list->next->content))
		pipe_stuff(v, list);
	else if (!is_now_or_prev(v, list))
		split_tokens(v, list->content);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

int       pipe_stuff(t_vars *v, t_list *list)
{
	pid_t   pid;
	int     fd[2];
	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		parent(v, list, fd);
	else
		child(v, list->next->next, fd);
	return(1);
}
