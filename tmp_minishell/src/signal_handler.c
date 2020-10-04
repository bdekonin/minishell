/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 11:14:16 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/25 13:47:52 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signo)
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGKILL)
		printf("received SIGKILL\n");
	else if (signo == SIGSTOP)
		printf("received SIGSTOP\n");
}

void	sig_catcher(void)
{
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
	{
		printf("\ncan't catch SIGUSR1\n");
		return ;
	}
	if (signal(SIGKILL, sig_handler) == SIG_ERR)
	{
		printf("\ncan't catch SIGKILL\n");
		return ;
	}
	if (signal(SIGSTOP, sig_handler) == SIG_ERR)
	{
		printf("\ncan't catch SIGSTOP\n");
		return ;
	}
}
