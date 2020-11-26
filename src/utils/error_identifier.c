/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_identifier.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 20:27:07 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/26 20:31:04 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int error_identifier(char *identifier)
{
	ft_putstr_fd(MINISHELL, 2);
	ft_putstr_fd(": unset: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (0);
}
