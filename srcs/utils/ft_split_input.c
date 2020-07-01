/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 10:35:33 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/01 18:11:12 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"
# define FLAGS "<|>"

t_cmd	*split_semicolen(char *string)
{
	t_cmd	*cmd_head = NULL;
	t_cmd	*cmd;
	char *str;
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
			str = ft_substr(string, 0, i); // leak
			cmd_head = cmd__ft_lstnew(type, ft_strtrim(str, " \t"));//protect
		}
		else
		{
			str = ft_substr(string, 0, i); // leak
			cmd = cmd__ft_lstnew(type, ft_strtrim(str, " \t")); //protect
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
*/void print_nodes(t_node *node);

int ft_split_input(char *line)
{
	char		**argv;
	size_t		size;
	int			i;
	t_node	*node_head;
	t_node	*node_list;
	t_cmd	*ret;

	node_head = NULL;
	argv = ft_split_sep(line, ";", &size);
	i = 0;	
	while (i < (int)size)
	{
		ret = split_semicolen(argv[i]);
		// if (!ret)
		if (!node_head)
		{
			node_head = node__ft_lstnew(&ret);
				// if (!node)
		}
		else
		{
			node_list = node__ft_lstnew(&ret);
			node__ft_lstadd_back(&node_head, node_list);
		}
		i++;
	}
	ft_free_array((void*)argv, size);
	print_nodes(node_head);
	node__ft_lstclear(&node_head, free);
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
		ft_printf("\n");
		node = node->next;
	}
	// node->cmd->next->type == '<'
}

// pwd1 | pwd2 > pwd3 | pwd4
// pwd | cat < test.txt

int main(void)
{
	ft_split_input("pwd1 | pwd2 > pwd3 | pwd4 ; pwd | cat < test.txt ; env ; env ; env");
	// ft_printf("\n");
	
	// ft_split_input("pwd | cat < test.txt");
	// ft_printf("\n");
	// ft_printf("\n");
	// ft_split_input("pwd | cat < test.txt");
}
