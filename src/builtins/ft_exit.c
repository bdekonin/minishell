/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 21:51:39 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/23 23:25:04 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	paramcounter(char **params)
{
	size_t i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

static int		printexits(int exitnum)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	if (exitnum == ARGCOUNT)
		ft_putendl_fd(MINISHELL_ARGCOUNT, STDERR_FILENO);
	else if (exitnum == NUMARG)
		ft_putendl_fd(MINISHELL_NUMARG, STDERR_FILENO);
	return (1);
}

int				ft_exit(t_vars *v, char **params)
{
	unsigned char	range;
	int				i;

	if (paramcounter(params) > 1)
		return (printexits(ARGCOUNT));
	if (paramcounter(params) == 0)
		ft_exit_error(v, EXIT_SUCCESS, 1);
	i = 0;
	while (params[0][i])
	{
		if (ft_isalpha(params[0][i]))
		{
			printexits(NUMARG);
			ft_exit_error(v, 255, 0);
		}
		i++;
	}
	range = (unsigned char)ft_atoi(params[0]);
	ft_exit_error(v, range, 0);
	return (1);
}

void			ft_exit_error(t_vars *v, int status, int print)
{
	// if (v->current_path)
	// 	free(v->current_path);
	// env__ft_lstclear(&v->env, free);
	if (errno && status == EXIT_FAILURE)
		ft_printf(MINISHELL_ERRNO, MINISHELL, strerror(errno));
	else if (print)
		ft_printf("exit\n");
	(void)print;
	(void)v;
	exit(status);
}
