/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 10:35:33 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/14 17:21:23 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** Will delete a cmd(node) when the head if == to list
**
** @param t_cmd *head	Starting location of te list.
** @param t_cmd *list	list to be deleted.
**
** @return N/A
*/

static void				cmd__delinvalid(t_cmd *head, t_cmd *list)
{
	while (head->next)
	{
		if (head->next == list)
		{
			cmd__ft_lstdelone(head->next, free);
			head->next = NULL;
			return ;
		}
		head = head->next;
	}
}

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


/*
** Returns te linked list of the current command.
**
** cmd[0] = The head pointer.
** cmd[1] = The new list to be added to cmd[0].
**
** @param  char *string		Current full command.
** @param  int i			Is the location of the First flag. \
**										ˆ(will be 0 if non found)
**
** @return t_cmd*			Returns the linked list of the curent command.
*/

static void printer(char *str, int i)
{
	int j = 0;

	while (str[j])
	{
		if (j == i)
			ft_printf("\x1B[31m%c\x1B[0m", str[i]);
		else
			ft_printf("%c", str[j]);
		j++;
	}
	ft_printf("\n");
}

static t_cmd	*line_to_linkedlist(char *string, int i)
{
	t_cmd	*cmd[2];

	cmd[0] = NULL;
	i = 1;
	while (1)
	{
		i = findflag(string, FLAGS);
		if (!i)
			i = ft_strlen(string);
		if (string[i + 1] == ANGLEBRACKETRIGHT)
		{
			string[i] = 32;
			string[i + 1] = ANGLEBRACKETDOUBLERIGHT;
			i = i + 1;
		}
		// printer(string, i);
		if (!cmd[0])
		{
			if (!getstring_and_newcmd(string, i, &cmd[0], string[i]))
				return (NULL);
		}
		else
		{
			if (!getstring_and_newcmd(string, i, &cmd[1], string[i]))
				return (NULL);
			cmd__ft_lstadd_back(&cmd[0], cmd[1]);
		}
		if (string[i] == ANGLEBRACKETDOUBLERIGHT)
		{
			string = ft_strchr(string, string[i]) + 1;	
			continue;
		}
		if (!findflag(string, FLAGS))
			break;
		string = ft_strchr(string, string[i]) + 1;	
		if (cmd__ft_lstlast(cmd[0])->line[0] == 0)
			cmd__delinvalid(cmd[0], cmd__ft_lstlast(cmd[0]));
	}
	return (cmd[0]);
}

void print_nodes(t_node *node, t_node *nodehead);

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
		ret = line_to_linkedlist(argv[i], 0);
		if (!ret)
			return (0);
		if (!v->nodehead)
		{
			v->nodehead = node__ft_lstnew(&ret);
			if (!v->nodehead)
				return (0);
		}
		else
		{
			node_list = node__ft_lstnew(&ret);
			if (!node_list)
				return (0);
			node__ft_lstadd_back(&v->nodehead, node_list);
		}
		i++;
	}
	ft_free_array((void*)argv, size);
	print_nodes(v->nodehead, v->nodehead);
	return (1);
}

void print_nodes(t_node *node, t_node *nodehead)
{
	t_cmd *cmd;

	int fd = open("/dev/ttys001", O_RDWR); // change to other terminal
	while (node)
	{
		cmd = node->cmd;
		while (cmd)
		{
			if (cmd->line[0] == 0)
				cmd__delinvalid(nodehead->cmd, cmd);
			// dprintf(fd, "\x1B[32msplit_input | %p - string = [%c][%s]\n\x1B[0m", node, cmd->type, cmd->line);
			cmd = cmd->next;
		}
		node = node->next;
	}
	// dprintf(fd, "\n\n\n\n\n\n\n\n\n\n");
}
//export PATH=/Users/bdekonin/minishell/noperm
