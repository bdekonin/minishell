/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _test.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/27 17:00:01 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int g_passed;
static int g_tests;

static int 		minishell(char *command, char **envp)
{
	t_vars	v;
	char	*cli;

	initialize(&v, envp, &cli);
	read_command_line_input(&v, command);
	ft_exit_error(&v, EXIT_SUCCESS, 0);
	return (0);
}

static char *getoutput(char *command, char **envp, int test)
{
	char *output;
	int fd[2];

	output = NULL;
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (test == 1)
			minishell(command, envp);
		else
		{
			waitpid(-1, NULL, 0);
			system(command);
		}
		exit(1);
	}
	else
		waitpid(-1, NULL, 0);
	close(fd[1]);
	ft_getline(fd[0], &output);
	return (output);
	(void)envp;
}

// static void strreplace(char *str, char replacefrom, char replaceto)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == replacefrom)
// 			str[i] = replaceto;
// 		i++;
// 	}
// }

static void printtest(char *command, int ok, char *me, char *og)
{
	if (ok == 0)
	{
		printf("\033[1;32m[%s]\n[OK]\n\n\033[0m", command);
		g_passed++;
	}
	else
	{
//		strreplace(me, '\n', '*');
//		strreplace(og, '\n', '*');
		printf("\033[1;31m[%s]\n[KO]\n\033[0m", command);
		printf("me - [%s] - [%d]\n", me, ok);
		printf("og - [%s] - [%d]\n\n", og, ok);
	}
	g_tests++;
	(void)me;
	(void)og;
}


static void runtest(char *command, char **envp)
{
	char *me;
	char *og;
	me = getoutput(command, envp, 1);
	og = getoutput(command, envp, 0);

	printtest(command, ft_strncmp(me, og, ft_strlen(me)), me, og);

	free(me);
	free(og);
}

#include <fcntl.h>
int main(int argc, char **argv, char **envp)
{	
	char *command;
	
	close(2);
	char **list;
	ft_getline(open("src/testingcommands.txt", O_RDONLY), &command);
	list = ft_split(command, '\n');
	for (int i = 0; list[i]; i++)
	{
		runtest(list[i], envp);
		free(list[i]);
	}
	free(list);
	printf("passed - %d\ntotal - %d\n", g_passed, g_tests);
	return (0);
	(void)argc;
	(void)argv;
}
