/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argumentadder.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 22:27:02 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/01 11:26:53 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline size_t returncount(char *command, char *file)
{
	return (ft_strlen(command) + 1 + ft_strlen(file) + 1);
}

static char *strjoiner(char *command, char *file)
{
	char *newcommand;
	int count;

	
	count = returncount(command, file);
	newcommand = ft_calloc(count, sizeof(char));
	if (!newcommand)
		return (NULL);
	ft_strlcat(newcommand, command, count);
	ft_strlcat(newcommand, file, count);
	free(command);
	return(newcommand);
}

int addarguments(t_list *list, int i)
{
	t_list *command;
	t_list *files;

	if (list->next && !is_redirection(list->next->content))
		return (0);
	if (list->next == NULL || list->next->next == NULL)
		return (0);
	command = list;
	files = list->next->next;
	if (ft_counter(files->content, "*") < 1)
		return (0);
	command->content = strjoiner(command->content, \
	ft_strchr(files->content, '*'));
	if (command->content == NULL)
		return (-1);
	*ft_strchr(files->content, '*') = '\0';
	return (1);
}