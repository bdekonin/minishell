/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 18:51:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/26 20:11:29 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 		main(int argc, char **argv, char **envp)
{
	t_vars	v;
	char	*cli;
	int		ret;

	ft_putendl_fd("Shell Starting up - version 1.0\n", 2);
	initialize(&v, envp, &cli);
	signal(SIGQUIT, signal_default);
	signal(SIGINT, signal_default);
	while (1)
	{
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		ret = get_next_line(STDIN_FILENO, &cli);
		if (ret == -2)
			ft_exit_error(&v, EXIT_SUCCESS, 1);
		if (ret < 0)
			ft_exit_error(&v, EXIT_FAILURE, 0);
		if (ret == 0)
			control_d(&v, &cli, ret);
		read_command_line_input(&v, cli);
		free(cli);
	}
	return (0);
	(void)argv;
	(void)argc;
}
