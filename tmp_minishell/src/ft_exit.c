/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 21:51:39 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/09/25 09:16:20 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_vars *v, char **params)
{
	ft_exit_error(v, EXIT_SUCCESS);
	return (1);
}

void	ft_exit_error(t_vars *v, int status)
{
	// free linked lists with: ft_lstclear(&head, free);
	if (v->prefix)
		free(v->prefix);
	if (v->current_path)
		free(v->current_path);
	if (v->temp)
		free(v->temp);
	if (v->stdout_copy) // if stdout has been copied.
	{
		dup2(v->fd, STDOUT_FILENO);
		close(v->fd);
		ft_printf("EXIT - EXIT NOW %d\n", v->stdout_copy);
		dup2(v->stdout_copy, 1);
		close(v->stdout_copy);
		ft_printf("EXIT - DONE\n");
	}
	ft_bzero(v, sizeof(t_vars)); // this will leak if we dont free everything, so testing purposes
	if (errno && status)
		ft_printf("%s\n", strerror(errno));
	else
		ft_printf("exit\n");
	exit(status);
}
