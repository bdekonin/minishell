/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 15:35:58 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/08 18:42:42 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_vars *v, char **params)
{
	ft_putendl_fd(v->current_path, 1);
	(void)(params);
	return (0);
}
