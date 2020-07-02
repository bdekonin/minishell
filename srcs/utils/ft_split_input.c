/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 10:35:33 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/02 11:22:19 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"
# define FLAGS "<|>"
# define TRIMS " \t"

static int	getstring_and_newcmd(char *string, int i, t_cmd **cmd, \
												unsigned char type)
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(string, 0, i);
	if (!tmp)
		return (0);
	tmp2 = ft_strtrim(tmp, TRIMS);
	free(tmp);
	if (!tmp2)
		return (0);
	*cmd = cmd__ft_lstnew(type, tmp2);
	if (!*cmd)
	{
		free(tmp2);
		return (0);
	}
	else
		return (1);
}

t_cmd	*split_semicolen(char *string)
{
	t_cmd	*cmd_head = NULL;
	t_cmd	*cmd;
	unsigned char type;
	int i;

	type = 1;
	while (type)
	{
		i = findflag(string, FLAGS);
		if (!i)
		{
			i = ft_strlen(string);
			type = 0;
		}
		else
			type = string[i];
		if (!cmd_head)
		{
			if (!getstring_and_newcmd(string, i, &cmd_head, type))
				return (NULL);
		}
		else
		{
			if (!getstring_and_newcmd(string, i, &cmd, type))
				return (NULL);
			cmd__ft_lstadd_back(&cmd_head, cmd);
		}
		string = ft_strchr(string, type) + 1;
	}
	return (cmd_head);
}

/*
** [0] = ;
** [1] = |
** [2] = >
** [3] = <
** pwd1 | pwd2 > pwd3 | pwd4
**
**
** pwd | cat < test.txt
*/

void print_nodes(t_node *node);

int ft_split_input(t_vars *v)
{
	char		**argv;
	size_t		size;
	int			i;
	t_node	*node_list;
	t_cmd	*ret;

	v->nodehead = NULL;
	argv = ft_split_sep(v->line, ";", &size);
	i = 0;
	while (i < (int)size)
	{
		ret = split_semicolen(argv[i]);
		if (!ret)
		{
			ft_printf("error\n");
			return (0);
		}
		if (!v->nodehead)
		{
			v->nodehead = node__ft_lstnew(&ret);
				// if (!node)
		}
		else
		{
			node_list = node__ft_lstnew(&ret);
			node__ft_lstadd_back(&v->nodehead, node_list);
		}
		i++;
	}
	ft_free_array((void*)argv, size);
	print_nodes(v->nodehead);
	return (1);
}

void print_nodes(t_node *node)
{
	t_cmd *cmd;
	while (node)
	{
		cmd = node->cmd;
		while (cmd)
		{
			ft_printf("%p - string = [%c][%s]\n", node, cmd->type, cmd->line);
			cmd = cmd->next;
		}
		node = node->next;
	}
}
