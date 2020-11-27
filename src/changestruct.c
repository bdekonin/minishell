/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   changestruct.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:41:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/27 12:14:05 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int swaparguments(t_vars *v, t_cmd *current)
{
	char	*newstring;
	char	*star;
	int		ret;

	if (current == NULL)
		return (0);
	if (ft_wordcount(current->line, '*') > 1 && current->type != ANGLEBRACKETLEFT)
	{
		star = ft_strchr(current->line, '*');
		if (current->prev == NULL)
			return (0);
		if (current->prev->type == ANGLEBRACKETLEFT || current->prev->type == PIPELINE)
			return (0);
		newstring = ft_strjoin(current->prev->line, star);
		malloc_check(v, newstring);
		*star = '\0';
		free(current->prev->line);
		current->prev->line = newstring;
	}
	ret = swaparguments(v, current->prev);
	return (ret);
}

static void nocommand_redir(t_vars *v, t_cmd *list)
{
	char *ptr;

	ptr = NULL;
	while (list)
	{
		if (!ft_strncmp(list->line, ">", 1) || !ft_strncmp(list->line, ">>", 2))
		{
			free(list->line);
			if (list->next && ft_wordcount(list->next->line, '*') > 1)
			{
				ptr = ft_strchr(list->next->line, '*');
				list->line = ft_strdup(ptr);
				*ptr = '\0';
			}
			else
				list->line = ft_strdup("");
			malloc_check(v, list->line);
			list->type = ANGLEBRACKETRIGHT;
		}
		list = list->next;
	}
}

static t_cmd *fix_anglebracketleft(t_cmd *list)
{
	t_cmd *temp;

	temp = NULL;
	if (!ft_strncmp(list->line, "<", 1))
	{
		temp = list->next;
		cmd__ft_lstdelone(list, free);
		return (temp);
	}
	return (list);
}
void	cmd__ft_printlist(t_cmd *cmd);

static void changefilenames(t_cmd *list)
{
	while (list)
	{
		if (is_redirection_new(list->type) && list->type != ANGLEBRACKETLEFT)
		{
			if (list->next != lastredir(list))
			{
				ft_swap(&list->next->line, &lastredir(list)->line);
				break;
			}
		}
		list = list->next;
	}
}
void	cmd__ft_printlist(t_cmd *cmd);
void		changestruct(t_vars *v, t_cmd *list)
{
	swaparguments(v, cmd__ft_lstlast(list));
	nocommand_redir(v, list);
	changefilenames(list);
	list = fix_anglebracketleft(list);
	v->cmd = list;
	// cmd__ft_printlist(list);
}