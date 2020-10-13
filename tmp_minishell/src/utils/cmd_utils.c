/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 11:39:18 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/13 11:39:47 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*cmd_str(int i)
{
	char	*cmd_str[BUILTINS + 1];

	cmd_str[0] = "echo";
	cmd_str[1] = "cd";
	cmd_str[2] = "pwd";
	cmd_str[3] = "export";
	cmd_str[4] = "unset";
	cmd_str[5] = "env";
	cmd_str[6] = "exit";
	return (cmd_str[i]);
}
