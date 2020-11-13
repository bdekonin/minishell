/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 22:12:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/13 15:24:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_quotations(const char *cli, char quotation_type)
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
	while (cli[i] != '\0' && !ft_charsearch(cli[i], "<>|;"))
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


static char gettype(char *content)
{
	char ret;

	ret = 0;
	if (!content)
		return (0);
	if (is_pipe(content))
		ret = PIPELINE;
	else if (is_redirection(content))
	{
		if (!ft_strncmp(content, ">>", 3))
			ret = ANGLEBRACKETDOUBLERIGHT;
		else if (!ft_strncmp(content, ">", 2))
			ret = ANGLEBRACKETRIGHT;
		else if (!ft_strncmp(content, "<", 2))
			ret = ANGLEBRACKETLEFT;
	}
	return (ret);
}
static t_cmd *addnewtoback(t_list *list)
{
	t_cmd *temp;

	char *linedup;
	char type;

	linedup = ft_strdup(list->content);
	if (linedup == NULL)
		return (NULL);
	type = gettype((list->next) ? list->next->content : NULL);
	temp = cmd__ft_lstnew(type, linedup);
	if (!temp)
	{
		free(linedup);
		return (NULL);
	}
	return (temp);
}

t_cmd *betterstruct(t_vars *v, t_list *list, t_cmd *head, t_cmd *temp)
{
	head = addnewtoback(list);
	if (head == NULL)
		ft_exit_error(v, EXIT_FAILURE, 1);
	list = list->next;
	while (list)
	{
		if (is_pipe(list->content) || is_redirection(list->content))
		{
			list = list->next;
			continue;
		}
		temp = addnewtoback(list);
		if (temp == NULL)
			ft_exit_error(v, EXIT_FAILURE, 1);
		cmd__ft_lstadd_back(&head, temp);
		list = list->next;
	}
	// cmd__ft_printlist(head); // niet nodig
	return (head);
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
	v->cmd = betterstruct(v, v->tempcmd, NULL, NULL);
	ft_lstclear(&v->tempcmd, free);
}
