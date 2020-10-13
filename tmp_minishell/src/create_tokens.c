/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 22:12:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/09 22:07:55 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	skip_quotations(const char *cli, char quotation_type)
{
	size_t i;

	i = 1;
	while (cli[i] && cli[i] != quotation_type && cli[i - 1] != '\\')
		i++;
	if (cli[i] == quotation_type)
		i++;
	return (i);
}

static size_t	get_len(const char *cli, size_t start)
{
	size_t i;

	i = start;
	if (ft_charsearch(cli[i], "<>|;"))
	{
		if (cli[i] == '>' && cli[i + 1] == '>')
			return (2);
		return (1);
	}
	while (cli[i] != '\0' && !ft_charsearch(cli[i], "<>| ;"))
	{
		if (cli[i] == '\'' && (i == 0 || cli[i - 1] != '\\'))
			i = i + skip_quotations(cli + i, '\'');
		else if (cli[i] == '\"' && (i == 0 || cli[i - 1] != '\\'))
			i = i + skip_quotations(cli + i, '\"');
		else
			i++;
	}
	return (i - start);
}

void				create_tokens(t_vars *v, const char *cli)
{
	size_t start;
	size_t len;
	
	start = 0;
	len = 0;
	while (cli[start] != '\0')
	{
		while (cli[start] == ' ')
			start++;
		len = get_len(cli, start);
		create_new_token(v, cli + start, len);
		start = start + len;
	}
}
//printf("start = [%lu] len = [%lu]\n", start, len);
