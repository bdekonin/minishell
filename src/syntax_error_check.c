/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error_check.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 15:24:18 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/05 16:10:45 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	skip_flags(const char *cli, size_t i)
{
	while (ft_charsearch(cli[i], "<>|;"))
		i++;
	while (cli[i] == ' ')
		i++;
	while (ft_charsearch(cli[i], "<>|;"))
		i++;
	return (i);
}

static size_t	skip_quotations_i(const char *cli, size_t i, char quotation)
{
	i++;
	while (cli[i] && cli[i] != quotation)
	{
		if (cli[i] == '\\' && cli[i + 1] == quotation)
			i++;
		i++;
	}
	return (i);
}

int				syntax_error_check(t_vars *v, const char *cli)
{
	size_t i;

	i = 0;
	while (cli[i] == ' ')
		i++;
	if (cli[i] == ';')
		return (syntax_error_return(v, ";"));
	if (cli[i] == '|')
		return (syntax_error_return(v, "|"));
	while (cli[i] != '\0')
	{
		if (cli[i] == '\'' && (i == 0 || cli[i - 1] != '\\'))
			i = skip_quotations_i(cli, i, '\'');
		else if (cli[i] == '\"' && (i == 0 || cli[i - 1] != '\\'))
			i = skip_quotations_i(cli, i, '\"');
		else if (ft_charsearch(cli[i], "<>|;"))
		{
			if (!check_flag_syntax(v, cli, i))
				return (0);
			i = skip_flags(cli, i);
		}
		i++;
	}
	return (1);
}

int				initial_syntax_error_check(t_vars *v, const char *cli)
{
	size_t i;

	if (!multiline_check(v, cli))
		return (0);
	i = 0;
	if (cli[i] == ';')
		return (syntax_error_return(v, ";"));
	while (cli[i] == ' ')
		i++;
	if (cli[i] == ';')
		return (syntax_error_return(v, ";"));
	return (1);
}

int				syntax_error_check_loop(t_vars *v, \
					char **args, size_t splitsize)
{
	size_t i;

	i = 0;
	while (i < splitsize)
	{
		if (!syntax_error_check(v, args[i]))
			return (0);
		i++;
	}
	return (1);
}
