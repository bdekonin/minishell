/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error_return.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 15:35:31 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/25 15:37:42 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int			syntax_error_return(t_vars *v, const char *token)
{
	v->cmd_ret = 258;
	ft_printf(SYNTAX_ERROR, MINISHELL, token);
	return (0);
}

static void	allow_ignore_pipe(const char *cli, size_t *i)
{
	*i += 1;
	if (cli[*i] == '|')
		*i += 1;
}

static void	allow_empty_pipe(const char *cli, size_t *i)
{
	*i += 1;
	while (cli[*i] == ' ')
		*i += 1;
	if (cli[*i] == '>' && cli[(*i) + 1] == '>')
		*i = *i + 2;
	else if (ft_charsearch(cli[*i], "<>"))
		*i += 1;
}

int			check_flag_syntax(t_vars *v, const char *cli, size_t i)
{
	if (cli[i] == '>' && cli[i + 1] == '>')
		i = i + 2;
	else if (cli[i] == '>')
		allow_ignore_pipe(cli, &i);
	else if (cli[i] == '|')
		allow_empty_pipe(cli, &i);
	else
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
