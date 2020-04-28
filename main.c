/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 10:35:22 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/28 13:57:28 by bdekonin      ########   odam.nl         */
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

	char *ptr;
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
		if (!ft_strncmp(argv[0], "exit", 5))
			exit(1);
		for (int i = 0; i < bultins; i++)
		{
			if (!ft_strncmp(cmd_str(i), argv[0], 8))
				printf("string %s, num %d\n", cmd_str(i), i);
		}
		if (ft_wordcount(line) > 1 && argv[1][ft_strlen(argv[1]) - 1] == 92)
		{
			removespace(argv + 1);
			ft_printf("%s\n", ptr);
		}
		for(int k = 0; k < ft_wordcount(line); k++)
			ft_printf("[%s]\n", argv[k]);
		free(line);
		// system("leaks a.out");
	}
}

void removespace(char **argv)
{
	ptr = argv[0];
	while (argv[1] != NULL && (argv[1][ft_strlen(argv[1]) - 1] == 92 ||
	argv[1][ft_strlen(argv[1]) - 1] == 47) && argv[1][0] != ';')
	{
		ptr = ft_strjoin(ptr, " ", argv[1]);
		if (argv[1][ft_strlen(argv[1]) - 1] == 47)
		{
			ft_memset(argv[1], strjoin_filler, ft_strlen(argv[1]));
			break ;
		}
		// Sets characters to NULL. So the program knows it has been read and copied.
		ft_memset(argv[0], strjoin_filler, ft_strlen(argv[0]));
		ft_memset(argv[1], strjoin_filler, ft_strlen(argv[1]));
		argv++;
	}
}
//    ptr
// cd one\ two\ three\ four/
//     0 .  1 .  2 .  3 .    4
