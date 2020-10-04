/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 22:12:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/23 15:55:56 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		create_new_node(t_vars *v, const char *cli, size_t len)
{
	t_list	*new;
	t_cmd	*node;

	node = ft_calloc(1, sizeof(t_cmd));
	if (!node)
		return (0);
	node->token = ft_substr(cli, 0, len);
	if (!node->token)
		return (ft_free_ret_int(node, 0));
	new = ft_lstnew(node);
	if (!new)
	{
		ft_free(node->token);
		ft_free(node);
	}
	ft_lstadd_back(&v->cmd, new);
	return (1);
}

static size_t	skip_quotations(const char *cli, char quotation)
{
	size_t i;

	i = 1;
	while (cli[i] && cli[i] != quotation && cli[i - 1] != '\\')
		i++;
	if (cli[i] == quotation)
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

int				create_tokens(t_vars *v, const char *cli)
{
	size_t start;
	size_t len;
	
	start = 0;
	len = 0;
	while (cli[start])
	{
		while (cli[start] == ' ')
			start++;
		len = get_len(cli, start);
		if (!create_new_node(v, cli + start, len))
			return (0);
		start = start + len;
	}
	return (1);
}
//printf("start = [%lu] len = [%lu]\n", start, len);
