/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 15:35:58 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/23 00:16:16 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_vars *v, char **params)
{
	ft_printf("%s\n", v->current_path);
	(void)(params);
	return (0);
}
