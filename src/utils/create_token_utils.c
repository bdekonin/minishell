/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_token_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 13:51:54 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/04 14:11:31 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t			skip_quotations(const char *cli, char quotation_type)
{
	size_t i;

	i = 1;
	while (cli[i] && cli[i] != quotation_type)
	{
		if (cli[i] == '\\' && cli[i + 1] == '\\')
			i++;
		else if (cli[i] == '\\' && cli[i + 1] == '\"')
			i++;
		i++;
	}
	return (i);
}

size_t			get_token_len(const char *cli, size_t start)
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
		if (cli[i] == '\\')
			i++;
		else if (cli[i] == '\'')
			i = i + skip_quotations(cli + i, '\'');
		else if (cli[i] == '\"')
			i = i + skip_quotations(cli + i, '\"');
		i++;
	}
	return (i - start);
}

void			add_bogus_token(t_vars *v)
{
	t_list	*list;
	char	*str;
	t_list	*lstnew;
	t_list	*temp;

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
