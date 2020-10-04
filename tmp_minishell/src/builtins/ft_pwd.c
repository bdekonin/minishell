/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 15:35:58 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/14 15:41:34 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_vars *v, char **params)
{
	v->current_path = getcwd(v->current_path, PATH_MAX);
	if (!v->current_path)
		ft_printf("ERROR\n");
//	else
//		if (!sethistory(&v->history_head, v->line, v->current_path))
//			return (0);
	ft_printf("%s\n", v->current_path);
	(void)(params);
	return (1);
}