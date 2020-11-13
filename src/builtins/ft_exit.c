/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 21:51:39 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/13 19:13:12 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void freeall(t_vars *v)
{
	// free linked lists with: ft_lstclear(&head, free);
	if (v->prefix)
		free(v->prefix);
	if (v->current_path)
		free(v->current_path);
	if (v->stdout_copy) // if stdout has been copied.
	{
		dup2(v->fd, STDOUT_FILENO);
		close(v->fd);
		dup2(v->stdout_copy, 1);
		close(v->stdout_copy);
	}
}

static size_t paramcounter(char **params)
{
	size_t i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

static int printexits(int exitnum)
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

int	ft_exit(t_vars *v, char **params)
{
	unsigned char range;
	int i;

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

void	ft_exit_error(t_vars *v, int status, int print)
{
	unsigned char range;

	freeall(v);
	// free env list
	ft_bzero(v, sizeof(t_vars)); // this will leak if we dont free everything, so testing purposes
	if (errno && status == 1)
		ft_printf("%s\n", strerror(errno));
	else if (print)
		ft_printf("exit\n");
	exit(status);
}
