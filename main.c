/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 10:35:22 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/10 19:40:42 by bdekonin      ########   odam.nl         */
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
int env__makelist(t_vars *v, char **envp);

void	read_user_input(t_vars *v);

int main(int argc, char **argv, char **envp)
{
	ft_printf("---- Starting ----\n\n");
	t_vars v;
	(void)argc; // voor de warnign
	(void)argv; // voor de warnign
	ft_bzero(&v, sizeof(v));
	ft_printf("pid = %d\n", getpid());
	/*
	** Initializing prompt
	*/
	v.prefix = ft_strdup(PREFIX);
	if (!v.prefix)
		ft_exit_error(&v, 1);
	v.current_path = ft_calloc(PATH_MAX, sizeof(char));
	if (!v.current_path) // free prefix
		ft_exit_error(&v, 1);
	v.current_path = getcwd(v.current_path, PATH_MAX);

	if (!env__makelist(&v, envp)) // leak in here
		ft_exit_error(&v, 1);
	// exit(1);
	/*
	** End initializing prompt
	*/
	signal(SIGINT, SIG_IGN); // ctrl c
	signal(SIGTSTP, SIG_IGN); // ctrl z

	while (1)
	{
		read_user_input(&v);
		node__ft_lstclear(&v.nodehead, free);
	}
}
