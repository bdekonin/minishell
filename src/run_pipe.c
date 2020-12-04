/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:38:28 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/04 12:40:18 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				pipe_stuff(t_vars *v, t_cmd *list); //declare in .h?

static void	child(t_vars *v, t_cmd *list, int *fd)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_exit_error(v, EXIT_FAILURE, 0);
	close(fd[1]);
	if (!list->prev || list->prev->type == 0 || list->prev->type == PIPELINE)
		split_tokens(v, list->line);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(v->cmd_ret);
}

static void	parent(t_vars *v, t_cmd *list, int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_exit_error(v, EXIT_FAILURE, 0);
	close(fd[0]);
	if (list->type == PIPELINE)
		pipe_stuff(v, list);
	else if (!list->prev || list->prev->type == 0 || list->prev->type == PIPELINE) // nee
		split_tokens(v, list->line);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

int			pipe_stuff(t_vars *v, t_cmd *list)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child(v, list, fd);
	else
	{
		waitpid(-1, NULL, 0);
		parent(v, list->next, fd);
	}
	return (1);
}

int			pipe_handler(t_vars *v, t_cmd *list)
{
	pid_t forky;
	int stat;

	forky = fork();
	if (forky < 0)
		ft_exit_error(v, EXIT_FAILURE, 1);
	else if (forky == 0)
	{
		pipe_stuff(v, list);
		exit(v->cmd_ret);
	}
	else
		waitpid(-1, &stat, 0);
	v->cmd_ret = WEXITSTATUS(stat);
	return (1);
}
