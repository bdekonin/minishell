/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 10:35:22 by bdekonin      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/04/30 20:34:25 by bdekonin      ########   odam.nl         */
=======
/*   Updated: 2020/04/28 20:58:33 by bdekonin      ########   odam.nl         */
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
<<<<<<< HEAD
=======
void removespace(t_vars *v, char **argv);
void	readline(t_vars *v);
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1

char		*cmd_str(int i)
{
	char	*cmd_str[bultins + 1];

	cmd_str[0] = "echo";
	cmd_str[1] = "cd";
	cmd_str[2] = "pwd";
	cmd_str[3] = "export";
	cmd_str[4] = "unset";
	cmd_str[5] = "env";
	cmd_str[6] = "exit";
	cmd_str[7] = "help";
	cmd_str[8] = NULL;
	return (cmd_str[i]);
}

char **getcmd(char *line)
{
	char **argv;

	argv = ft_split(line, ' ');
	return (argv);
}

<<<<<<< HEAD
void ctrl_c()
{
	return ;
}

=======
	char *ptr;

void test()
{
	// exit(EXIT_FAILURE);
}
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
int main(void)
{
	ft_printf("--- Starting ----\n\n");
	t_vars v;
<<<<<<< HEAD
	
	/*
	** Initializing prompt
	*/
=======

/*
** Initializing prompt
*/
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
	v.prefix = ft_strdup(d_prefix);
	if (!v.prefix)
		return (0);
	v.current_path = ft_calloc(path_max, sizeof(char));
	if (!v.current_path)
		return (0);
	v.current_path = getcwd(v.current_path, path_max);
<<<<<<< HEAD
=======

/*
** End initializing prompt
*/
	int stat;
		signal(SIGINT, test);
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1

	/*
	** End initializing prompt
	*/
	int stat;
	signal(SIGINT, ctrl_c);
	while (1)
	{
		readline(&v);
		if (v.forky > 0)
<<<<<<< HEAD
		{
			wait(&stat);
			printf("Im the parent now and im closing\n");
			printf("%d - %d - %d\n", WTERMSIG(stat), WEXITSTATUS(stat), WIFSIGNALED(stat));
		}
		if (!WIFSIGNALED(stat) && WEXITSTATUS(stat) == EXIT_SUCCESS)
		{
			printf("[%d] - Child Success - %d\n", v.forky, WEXITSTATUS(stat));
			exit(EXIT_SUCCESS);
		}
		if (WTERMSIG(stat) == SIGSEGV)
		{
			printf("[%d] - Child SEGFAULTED - %d\n", v.forky, WEXITSTATUS(stat));
			readline(&v);
		}
	}
}

void cmd(t_vars *v, char **params)
{
	int (*p[8]) (t_vars *v, char **params);

	p[0] = echo;
	p[1] = cd;
	p[2] = pwd;
	p[3] = export;
	p[4] = unset;
	p[5] = env;
	p[6] = exitt;
	p[7] = help;
	for (int i = 0; i < bultins; i++)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 15))
			(*p[i]) (v, params);
	}
}

void	readline(t_vars *v)
{
	v->forky = fork();
=======
		{
			wait(&stat);
			printf("Im the parent now and im closing\n");
		}
		if (WEXITSTATUS(stat) == EXIT_SUCCESS)
		{
			printf("[%d] - Child Success - %d\n", v.forky, WEXITSTATUS(stat));
			exit(EXIT_SUCCESS);
		}
		if (WEXITSTATUS(stat) == EXIT_FAILURE) // Probably delete this. Use this to simulate segfault
			exit(EXIT_SUCCESS);
		if (WTERMSIG(stat) > 0)
		{
			printf("[%d] - Child Failed - %d\n", v.forky, WEXITSTATUS(stat));
			readline(&v);
		}
	}
}


void	readline(t_vars *v)
{
	v->forky = fork();
	// ft_printf("Current\t[%d]\nParent\t[%d]\n", getpid(), getppid());
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
	while (!v->forky)
	{
		ft_printf(v->prefix, ft_strrchr(v->current_path, '/') + 1);
		v->ret = get_next_line(STDIN_FILENO, &v->line);
		if (v->ret < 0)
			exit(1);
		if (*v->line != 0)
		{
			v->argv = getcmd(v->line);
			if (!v->argv)
				exit(1);
<<<<<<< HEAD
			if (!ft_strncmp(v->argv[0], "segfault", 20))
			{
				ft_memset(NULL, 1, 1);
			}
			else if (!ft_strncmp(v->argv[0], "parent", 20))
				ft_printf("[%d]\n", getppid());
			else if (!ft_strncmp(v->argv[0], "pid", 4))
				ft_printf("[%d]\n", getpid());
			else if (!ft_strncmp(v->argv[0], "exit", 5))
				exit(EXIT_SUCCESS);
			else
			{
				cmd(v, v->argv);
			}
=======
			if (!ft_strncmp(v->argv[0], "exit", 5))
				exit(0);
			else if (!ft_strncmp(v->argv[0], "segfault", 20))
				ft_memset(NULL, 1, 1);
			else if (!ft_strncmp(v->argv[0], "parent", 20))
				ft_printf("[%d]\n", getppid());
			else if (!ft_strncmp(v->argv[0], "current", 4))
				ft_printf("[%d]\n", getpid());
			else if (ft_wordcount(v->line) > 1 && v->argv[1][ft_strlen(v->argv[1]) - 1] == 92)
				removespace(v, v->argv + 1);
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
		}
		free(v->line);
	}
	// exit(EXIT_FAILURE);
}
<<<<<<< HEAD
=======

//    ptr
// cd one\ two\ three\ four/
//     0 .  1 .  2 .  3 .    4
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
