/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:38:28 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/27 11:36:16 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void runParentt(int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
}
static void runChildd(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}
static void runFinish(t_vars *v)
{
	reset_std(v);
}

int	run_pipe(t_vars *v, char *parentCommand, char *childCommand, int *fd)
{
	pid_t pid;

	pipe(fd);
	pid = fork();
	if (pid != 0) // Child
	{
		runChildd(fd);
		system(childCommand);
	}
	else // parent
	{
		runParentt(fd);
		system(parentCommand);
	}
	if (pid == 0)
		exit(3);
	runFinish(v);
	return (1);
}


# define STD_PIPECOUNTER 0;



void getstdin(t_vars *vars)
{
	char *temp;
	dprintf(vars->stdout_copy, "reading from stdin now\n");
	ft_getline(STDIN_FILENO, &temp);
	dprintf(vars->stdout_copy, "\tstdin = [%s]\n", temp);
}
void getstdout(t_vars *vars)
{
	char *temp;
	dprintf(vars->stdout_copy, "reading from stdout now\n");
	ft_getline(STDOUT_FILENO, &temp);
	dprintf(vars->stdout_copy, "\tstdout = [%s]\n", temp);
}
void getPIPE(t_vars *vars, int *pipe, char *ptr)
{
	close(pipe[1]);
	char *temp;
	dprintf(vars->stdout_copy, "%s", ptr);
	ft_getline(pipe[0], &temp);
	dprintf(vars->stdout_copy, "\t\tpipe = [%s]\n", temp);
}

int first_pipe(t_vars *v, t_list *list)
{
	int pipecounter;

	pipecounter = STD_PIPECOUNTER;

	pipe(v->pipefd);
	v->forky = fork();
	if (v->forky != 0) // Child
	{
		runChildd(v->pipefd);
		system(list->next->next->content); // wc
	}
	else // Parent
	{
		runParentt(v->pipefd);
		system(list->content); // pwd
	}

	//parent wait for child
	//child goes in loop,
	if (v->forky == 0)
		exit(1);
	return (pipecounter);
}

t_list *lastpipe(t_list *headptr);
// pwd | wc | cat -e
int pipe_next(t_vars *v, t_list *list, int *oldPipe, int first, int *opper_fd)
{
	int newPipe[2];

	if (list->next && is_pipe(list->next->content))
	{
		if (pipe(newPipe) < 0)
		{
			dprintf(v->stdout_copy, "Pipe Error\n");
			ft_exit_error(v, EXIT_FAILURE);
		}
		v->forky = fork();
		if (first == 0)
		{
			close(oldPipe[1]);
			dup2(oldPipe[0], STDIN_FILENO);
		}
		if (v->forky == 0) // Child
		{
			int test = -1;
			// Child
			// dprintf(v->stdout_copy, "Child\n");
			if (list->next->next == lastpipe(list))
            {
				close(opper_fd[0]);
				close(STDOUT_FILENO);
				dup2(opper_fd[1], STDOUT_FILENO);
				// ft_printf("%s=", list->content);
				test = 1;
            }
			else
			{
				close(newPipe[0]);
				close(STDOUT_FILENO);
				dup2(newPipe[1], STDOUT_FILENO);
				// ft_printf("%s=", list->content);
				test = 0;
			}
			// dprintf(v->stdout_copy, "[%d] - [%d] - Child %d Command - [%s]\n", getpid(), v->forky, test, list->content);
			system(list->content);

			exit(EXIT_SUCCESS);
		}
		else if (v->forky > 0) // Parent
		{
			// Parent
			wait(NULL);
			// dprintf(v->stdout_copy, "Parent\n");
		}
		else // Error
		{

			// Error
			// dprintf(v->stdout_copy, "Fork Error\n");
		}
		// ft_printf("[%d] - [%d] - Command - [%s]\n", getpid(), v->forky, list->content);
		// dprintf(v->stdout_copy, "callback\n");
		pipe_next(v, list->next->next, newPipe, 0, opper_fd);
	}
	else
	{
		// ft_printf("[%d] - [%d] - LAST COMMAND IN PARENT - [%s]\n", getpid(), v->forky, list->content);
		// getPIPE(v, opper_fd, "\tlast reading pipe\n");
		
		
		close(opper_fd[1]);
		dup2(opper_fd[0], STDIN_FILENO);
		system(list->content);
	}

	return (1);
}
