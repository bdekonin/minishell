/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   changestruct.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:41:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/15 16:59:45 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int swaparguments(t_cmd *current)
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
		// Malloc Check
		*star = '\0';
		free(current->prev->line);
		current->prev->line = newstring;
	}
	ret = swaparguments(current->prev);
	return (ret);
}
static void nocommand_redir(t_cmd *list)
{
	t_cmd *head = list; // temp
	char *ptr;

	ptr = NULL;
	while (list)
	{
		if (!ft_strncmp(list->line, ">", 1))
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
			list->type = ANGLEBRACKETRIGHT;
		}
		list = list->next;
	}
	// cmd__ft_printlist(head); // niet nodig
}

static void changefilenames(t_cmd *list)
{
	while (list)
	{
		if (is_redirection_new(list->type) && list->type != ANGLEBRACKETLEFT)
		{
			if (list->next != lastredir(list))
			{
				// ft_printf("sdsdsd");
				ft_swap(&list->next->line, &lastredir(list)->line);
				break;
			}
		}
		list = list->next;
	}
}
// echo hallo <file1 >file2
void		changestruct(t_vars *v, t_cmd *list)
{
	swaparguments(lastredir(list));
	nocommand_redir(list); // (> o pwd) && (> o)
	changefilenames(list); // echo hoi > file1 hallo > file2 welkom > file3 lars > file4 bob
}