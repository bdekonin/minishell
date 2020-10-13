/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error_check.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 15:24:18 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/09 20:38:32 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		syntax_error_return(t_vars *v, const char *token)
{
	ft_printf(SYNTAX_ERROR, v->default_executable->content, token);
	return (0);
}

static int		check_flag_syntax(t_vars *v, const char *cli, size_t i)
{
	if (cli[i] == '>' && cli[i + 1] == '>')
		i = i + 2;
	else if (ft_charsearch(cli[i], "<>|;"))	
		i++;
	while (cli[i] == ' ')
		i++;
	if (cli[i] == '>' && cli[i + 1] == '>')
		return (syntax_error_return(v, ">>"));
	if (cli[i] == '>')
		return (syntax_error_return(v, ">"));
	if (cli[i] == '<')
		return (syntax_error_return(v, "<"));
	if (cli[i] == ';')
		return (syntax_error_return(v, ";"));
	if (cli[i] == '|')
		return (syntax_error_return(v, "|"));
	if (cli[i] == '\0')
		return (syntax_error_return(v, "newline"));
	return (1);
}	

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

static size_t	skip_quotations(const char *cli, size_t i, char quotation)
{
	i++;
	while (cli[i] && cli[i] != quotation && cli[i - 1] != '\\')
		i++;
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
			i = skip_quotations(cli, i, '\'');
		else if (cli[i] == '\"' && (i == 0 || cli[i - 1] != '\\'))
			i = skip_quotations(cli, i, '\"');
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
