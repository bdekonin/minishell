/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 09:47:46 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/12/02 14:00:07 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_default(int siggie)
{
	if (siggie == SIGINT)
	{
		ft_putendl_fd("\b\b  ", STDOUT_FILENO);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
	if (siggie == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
}

void	signal_execve(int siggie)
{
	signal(siggie, signal_execve);
}
