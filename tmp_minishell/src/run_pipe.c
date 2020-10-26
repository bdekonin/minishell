/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_pipe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:38:28 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/26 15:54:12 by lverdoes      ########   odam.nl         */
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
	// ft_printf("frst: [%s]\n", list->co, v->forkyntent);
	if (list->next && is_pipe(list->next->content))
	{	
		if (pipe(newPipe) < 0)
			exit(EXIT_FAILURE);
		v->forky = fork();
		if (v->forky == 0) // Child
		{
			if (first != 1)
			{
				close(oldPipe[1]);
				dup2(oldPipe[0], STDIN_FILENO);
			}
			// oldPipe[0] to stdin
			// stdout to newPipe[write]
			if (list->next->next == lastpipe(list))
			{
				//printf("1:[%p] 2:[%p]\n", list->next->next, lastpipe(list));
				//ft_printf("list->next = nextpipe\n");
				close(opper_fd[0]);
				dup2(opper_fd[1], STDOUT_FILENO);
			}
			else
			{
				close(newPipe[0]);
				dup2(newPipe[1], STDOUT_FILENO);
				//ft_printf("[%d] - [%d] - child: %s\n", getpid(), v->forky, list->content);
			}
			dprintf(v->stdout_copy, "testje %s\n", list->content);
		//	printf("kaaleee\n");
			system(list->content);
			dprintf(v->stdout_copy, "testje2 %s\n", list->content);
			pipe_next(v, list->next->next, newPipe, 0, opper_fd);
		}
		else if (v->forky > 0) // Parent
		{
			// newPipe[read] to stdin
			// stdout to newPipe[write]
			ft_printf("[%d] - [%d] - parent: waiting on %s\n\n", getpid(), v->forky, list->content);
			wait(NULL);
		}
		else // FORK ERRRRROR
			exit(EXIT_FAILURE);
	}
	if (v->forky == 0)
		exit(EXIT_SUCCESS);
	if (first == 0)
		exit(EXIT_SUCCESS);
	else //parent cmds
	{
		char *test;
		close(opper_fd[1]);
		dup2(opper_fd[0], STDIN_FILENO);
		ft_putendl_fd(lastpipe(list)->content, STDOUT_FILENO);
		system(lastpipe(list)->content);
		// ft_getline(opper_fd[0], &test);
		// ft_printf("testie=[%s]\n", test);
		// HIERZO LARSIE
		// dup2(stdout, stdin);
		ft_printf("[%d] - [%d] - LAST COMMAND IN PARENT - [%s]\n", getpid(), v->forky, lastpipe(list)->content);
	}
	return (1);
}
