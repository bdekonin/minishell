/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 22:12:44 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/27 17:17:58 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t			skip_quotations(const char *cli, char quotation_type)
{
	size_t i;

	i = 1;
	while (cli[i] && cli[i] != quotation_type)
	{
//		if (cli[i] == '\\' && cli[i + 1] == quotation_type)
		if (cli[i] == '\\' && cli[i + 1] == '\"')
			i++;
		i++;
	}
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
//		if (cli[i] == '\'' && (i == 0 || cli[i - 1] != '\\'))
		if (cli[i] == '\'')
			i = i + skip_quotations(cli + i, '\'');
		else if (cli[i] == '\"' && (i == 0 || (cli[i - 1] != '\\' && cli[i - 2] != '\\'))) //hiero
			i = i + skip_quotations(cli + i, '\"');
		i++;
	}
	return (i - start);
}

static char 	gettype(char *content)
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
static t_cmd 	*addnewtoback(t_list *list)
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

// static void	print_tokens(t_list *tmp) // tmp debug function
// {
// 	while (tmp)
// 	{
// 		printf("list token = [%s]\n", tmp->content);
// 		tmp = tmp->next;
// 	}
// }

static t_cmd	*betterstruct(t_vars *v, t_list *list, t_cmd *head, t_cmd *temp)
{
//	print_tokens(list);
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
		malloc_check(v, temp);
		cmd__ft_lstadd_back(&head, temp);
		list = list->next;
	}
	//print_token(list);
	// cmd__ft_printlist(head);
	return (head);
}

void		add_bogus_token(t_vars *v)
{
	t_list *list;
	char *str;
	t_list *lstnew;
	t_list *temp;

	list = v->tempcmd;
	while (list)
	{
		if (is_pipe(list->content))
        {
            if (list->next && is_redirection(list->next->content))
            {
                str = ft_strdup("");
				lstnew = ft_lstnew(str);
				temp = list->next;
				list->next = lstnew;
                list->next->next = temp;
            }
        }
		list = list->next;
	}
}

void			create_tokens(t_vars *v, const char *cli)
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
	add_bogus_token(v);
	v->cmd = betterstruct(v, v->tempcmd, NULL, NULL);
	ft_lstclear(&v->tempcmd, free);
}