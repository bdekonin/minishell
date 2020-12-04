/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmd_print_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 16:40:30 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/12/04 14:52:51 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "../../minishell.h"

void	cmd__ft_printlist(t_cmd *cmd) //deze moet er nog uit toch?
{
	int i;

	i = 0;
	while (cmd)
	{
		//dprintf(2, "[%d] - [%s] - [%c]\n", i, cmd->line, cmd->type);
		i++;
		cmd = cmd->next;
	}
	//dprintf(2, "\n");
	return ;
}