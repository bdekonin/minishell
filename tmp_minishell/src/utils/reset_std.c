/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_std.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 23:01:11 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/27 19:47:13 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int reset_stdin(t_vars *v)
{
	dup2(v->stdin_copy, 0);
	close(v->stdin_copy);
	v->stdin_copy = 0;
	return (1);
}

static int reset_stdout(t_vars *v)
{
	dup2(v->stdout_copy, 1);
	close(v->stdout_copy);
	v->stdout_copy = 0;
	return (1);
}

// static int	close_pipefd(t_vars *v)
// {
// 	if (v->pipefd[0] != -1)
// 	{
// 		close(v->pipefd[0]);
// 		v->pipefd[0] = -1;
// 	}
// 	if (v->pipefd[1] != -1)
// 	{
// 		close(v->pipefd[1]);
// 		v->pipefd[1] = -1;
// 	}
// 	return (1);
// }

int	reset_std(t_vars *v)
{
	if (v->stdout_copy)
		reset_stdout(v);
	if (v->stdin_copy)
		reset_stdin(v);
//	close_pipefd(v);
	return (1);
}
