/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiline_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 14:04:18 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/14 09:50:39 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_double_quote(t_vars *v, const char *cli, size_t *i)
{
	*i += 1;
	while (cli[*i] != '\"')
	{
		if (cli[*i] == '\0')
			return (syntax_error_return(v, "\""));
		if (cli[*i] == '\\')
			*i += 1;
		*i += 1;
	}
	return (1);
}

static int	check_single_quote(t_vars *v, const char *cli, size_t *i)
{
	*i += 1;
	while (cli[*i] != '\'')
	{
		if (cli[*i] == '\0')
			return (syntax_error_return(v, "\'"));
		*i += 1;
	}
	return (1);
}

int			multiline_check(t_vars *v, const char *cli)
{
	size_t	i;
	int		count_double;
	int		count_single;

	count_double = 0;
	count_single = 0;
	i = 0;
	if (ft_strlen(cli) == 1 && cli[0] == '\\')
		return (syntax_error_return(v, "\\"));
	while (cli[i] != '\0')
	{
		if (cli[i] == '\\')
			i++;
		else if (cli[i] == '\'' && !check_single_quote(v, cli, &i))
			return (0);
		else if (cli[i] == '\"' && !check_double_quote(v, cli, &i))
			return (0);
		i++;
	}
	return (1);
}
