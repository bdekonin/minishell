/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 21:51:39 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/08 14:24:17 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"


static inline void checkif_freed_else_i_will_free_everything(t_vars *v)
{
	int i;

	i = 0;
	if (v->prefix)
		free(v->prefix);
	if (v->current_path)
		free(v->current_path);
	if (v->line)
		free(v->line);
	/*
	** export PATH=/Users/bdekonin/minishell/noperm
	** s
	*/
	if (v->cmdlist) // dont work if you do 
	{
		while (v->cmdlist[i])
		{
			cmd__ft_lstclear(&v->cmdlist[i], free);
			i++;
		}
		free(v->cmdlist);
	}
}

void	ft_exit_error(t_vars *v, int status)
{
	v->exit_status = status;
	ft_exit(v, NULL, NULL, NULL);
}

int ft_exit(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	int stat_temp = v->exit_status; //do this because bzero will be overwritten

	env__ft_lstclear(&v->env_head, free);
	his__ft_lstclear(&v->history_head, free);
	checkif_freed_else_i_will_free_everything(v);

	ft_bzero(v, sizeof(t_vars)); // this will leak if we dont free everything, so testing purposes
	system("leaks minishell");
	if (errno)
		ft_printf("%s\n", strerror(errno));
	else
		ft_printf("exit\n");
	exit(stat_temp);

	(void)(params);
	(void)(cmd);
	(void)(ret);
	return (1);
}
