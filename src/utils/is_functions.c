/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_functions.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 22:30:43 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/14 15:03:01 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection_new(unsigned char type)
{
	if (type == ANGLEBRACKETLEFT)
		return (1);
	if (type == ANGLEBRACKETRIGHT)
		return (1);
	if (type == ANGLEBRACKETDOUBLERIGHT)
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, ">>", 3) || \
		(!ft_strncmp(str, ">", 2)) || \
		(!ft_strncmp(str, "<", 2)))
		return (1);
	return (0);
}

int	is_pipe(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "|", 2))
		return (1);
	return (0);
}

int	is_semicolon(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, ";", 2))
		return (1);
	return (0);
}
