/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 10:35:22 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/17 09:29:42 by bdekonin      ########   odam.nl         */
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

void ctrl_c()
{
	return ;
}

int segfault = 0;

void env__makelist(t_vars *v, char **envp)
{
	t_env	*env;
	char	*name;
	char	*content;
	int		loc;
	int		i;

	i = 1;
	loc = ft_charsearch(envp[0], '='); // make better function; universal one
	name = ft_substr(envp[0], 0, loc);
		// name protect
	content = ft_substr(envp[0], loc + 1, ft_strlen(envp[0] + loc));
		//content protect
	env = env__ft_lstnew(name, content);
	while (envp[i])
	{
		loc = ft_charsearch(envp[i], '='); // make better function; universal one
		name = ft_substr(envp[i], 0, loc);
			// name protect
		content = ft_substr(envp[i], loc + 1, ft_strlen(envp[i] + loc));
			//content protect
		env__ft_lstadd_back(&env, env__ft_lstnew(name, content));
		i++;
	}
	v->env_head = env;
}

int main(int argc, char **argv, char **envp)
{
	ft_printf("--- Starting ----\n\n");
	t_vars v;
	argc++; //  TIJDELIJK VOOR DE WARNING
	argv[0] = NULL; // TIJDELIJK VOOR DE WARNING

	env__makelist(&v, envp);
	/*
	** Initializing prompt
	*/
	v.prefix = ft_strdup(d_prefix);
	if (!v.prefix)
		return (0);
	v.current_path = ft_calloc(path_max, sizeof(char));
	if (!v.current_path)
		return (0);
	v.current_path = getcwd(v.current_path, path_max);

	/*
	** End initializing prompt
	*/

	v.argc = 0;
	int stat;
	signal(SIGINT, ctrl_c);
	while (1)
	{
		readline(&v);
		if (v.forky > 0)
		{
			wait(&stat);
			// printf("Im the parent now and im closing\n");
			printf("%d - %d - %d\n", WTERMSIG(stat), WEXITSTATUS(stat), WIFSIGNALED(stat));
		}
		// if (!WIFSIGNALED(stat) && WEXITSTATUS(stat) == EXIT_FAILURE)
		// {
		// // 	readline(&v);
		// }
		if (!WIFSIGNALED(stat) && WEXITSTATUS(stat) == EXIT_SUCCESS)
		{
			// printf("[%d] - Child Success - %d\n", v.forky, WEXITSTATUS(stat));
			exit(EXIT_SUCCESS);
		}
		if (WTERMSIG(stat) == SIGSEGV)
		{
		// 	// printf("[%d] - Child SEGFAULTED - %d\n", v.forky, WEXITSTATUS(stat));
			ft_printf("\nSomething went wrong!\nRestarting\n\n");
		// 	// // // // segfault = 1; // DIT
		// 	readline(&v);
		}
	}
}

void	param_to_lower_case(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

void cmd(t_vars *v, char **params)
{
	int i;

	i = 0;
	if (!ft_strncmp("getpid", params[0], 10))	// Used for checking which parent and pid it is.
		ft_printf("%d\n", getpid());			// If you do leaks (filename) and then select the child id (most likely option b)
	if (!ft_strncmp("getppid", params[0], 10))
		ft_printf("%d\n", getppid());
	int (*p[8]) (t_vars *v, char **params);

	p[0] = echo;
	p[1] = cd;
	p[2] = pwd;
	p[3] = export;
	p[4] = unset;
	p[5] = env;
	p[6] = exitt;
	p[7] = help;
	param_to_lower_case(params[0]);
	while (i < bultins)
	{
		if (!ft_strncmp(cmd_str(i), params[0], 15))
		{
			(*p[i])(v, params);
			return ;
		}
		i++;
	}
	ft_printf(cmd_notfound, params[0]);
}

void	readline(t_vars *v)
{
	v->forky = fork();
	while (!v->forky)
	{
		v->ptr = NULL; // for cd but probably change.
		ft_printf(v->prefix, ft_strrchr(v->current_path, '/') + 1);
		v->ret = get_next_line(STDIN_FILENO, &v->line);
		if (v->ret < 0)
			exit(1);
		if (*v->line != 0)
		{
			v->argv = getcmd(v->line);
			if (!v->argv)
				exit(EXIT_FAILURE);
			if (!ft_strncmp(v->argv[0], "segfault", 20))
			{
				ft_memset(NULL, 1, 1);
			}
			else
				cmd(v, v->argv);
		}
		free(v->line);
		ft_free_array((void*)v->argv, ft_wordcount(v->line));
	}
}
