/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 11:05:24 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/27 20:54:18 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		check_valid_identifier(char *arg)
{
	size_t i;

	i = 0;
	if (arg[i] != '\0' && !ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	i++;
	while (arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]))
			i++;
		else if (arg[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int				ft_unset(t_vars *v, char **params)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = 0;
	while (params[i])
	{
		if (!check_valid_identifier(params[i]))
		{
			ret = 1;
			error_identifier(params[i]);
		}
		env__ft_lstremove_middle(params[i], v->env);
		i++;
	}
	return (ret);
}
