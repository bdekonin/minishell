/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 15:35:58 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/20 17:04:05 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_vars *v, char **params)
{
	v->current_path = getcwd(v->current_path, PATH_MAX);
	malloc_check(v, v->current_path);
	ft_printf("%s\n", v->current_path);
	(void)(params);
	return (0);
}