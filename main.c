/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 10:35:22 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/27 07:51:21 by bdekonin      ########   odam.nl         */
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
void removespace(char **argv);

char *prefix;
char *current_path;
int comma = -1;
int arg_i = 0;

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
	if (!argv)
		return (NULL);
	return (argv);
}

	char *newline;
int main(void)
{
	ft_printf("--- Starting ----\n\n");

	char *line;
	int ret;
	char **argv;

/*
** Initializing prompt
*/
	prefix = ft_strdup(d_prefix);
	if (!prefix)
		return (0);
	current_path = ft_calloc(path_max, sizeof(char));
	if (!current_path)
		return (0);
	current_path = getcwd(current_path, path_max);
/*
** End initializing prompt
*/

	while (1)
	{
		ft_printf(prefix, ft_strrchr(current_path, '/') + 1);
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret < 0)
			return (-1);
		argv = getcmd(line);
		if (!argv)
			return (-1);
		// for (int i = 0; i < bultins; i++)
		// {
		// 	if (!ft_strncmp(cmd_str(i), argv[0], 8))
		// 		printf("string %s, num %d\n", cmd_str(i), i);
		// }
		if (ft_wordcount(line) > 1 && argv[1][ft_strlen(argv[1]) - 1] == 92)
		{
			removespace(argv);
			ft_printf("%s\n", newline);
		}
		free(line);
		free(argv);
	}
}
	static int i = 0;
void removespace(char **argv)
{
	newline = ft_strdup("");
	while (argv[1] != NULL && argv[1][0] != ';')
	{
		i++;
		newline = ft_strjoin(newline, argv[1]);
		argv[1] = ft_strjoin(argv[1], argv[2]);
		// printf("Argument 0 [%s]\t1 [%s]\t2 [%s]\n", argv[0], argv[1], argv[2]);
		argv++;
	}
}

// cd one\ two\ three\ four/
//      0 .  1 .  2 .  3 .    4