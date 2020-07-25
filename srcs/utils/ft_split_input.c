/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 10:35:33 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/25 12:28:02 by bdekonin      ########   odam.nl         */
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

static t_cmd	*line_to_linkedlist(char *string, int i, char *executable)
{
	t_cmd	*cmd[2];

	cmd[0] = NULL;
	i = 1;
	while (1)
	{
		i = findflag(string, FLAGS);
		if (!i)
			i = ft_strlen(string);
		if (string[i + 1] == ANGLEBRACKETRIGHT && \
		string[i + 2] == ANGLEBRACKETRIGHT)
		{
			ft_printf(SYNTAX_ERROR, executable, '>');
			errno = 0;
			return (0);
		}
		if (string[i + 1] == ANGLEBRACKETRIGHT)
		{
			string[i] = 32;
			string[i + 1] = ANGLEBRACKETDOUBLERIGHT;
			i = i + 1;
		}
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
void verify_nodes(t_node *node, t_node *nodehead);
char *ft_quote(char *line, char type);

int ft_split_input(t_vars *v)
{
	char		**argv;
	size_t		size;
	int			i;
	t_node	*node_list;
	t_cmd	*ret;

	v->nodehead = NULL;
	argv = ft_split_sep_exep(v->line, ";", &size);
	i = 0;
	while (i < (int)size)
	{
		if (ft_counter(argv[i], '\"') % 2 || ft_counter(argv[i], '\'') % 2)
		{
			argv[i] = ft_quote(argv[i], (ft_counter(argv[i], '\"') % 2) ? '\"' : '\'');
			if (!argv[i])
				return (0);
		}
		ret = line_to_linkedlist(argv[i], 0, v->__executable->content);
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
	verify_nodes(v->nodehead, v->nodehead);
	print_nodes(v->nodehead, v->nodehead);
	return (1);
}
 //cat < doei.txt < hallo.txt
char *check_arguments(t_cmd *cmdhead, t_cmd *cmd, char *line)
{
	int		fd;
	size_t	space_location;
	char	oldchar;
	char	*temp;
	if (!ft_counter(line, 32)) // change to that it doesnt get one with a \ before so "Test\ ing\ ing/" is one word not space
		return (line);
	
	space_location = ft_strchr(line, 32) - line;
	oldchar = line[space_location];
	line[space_location] = 0;

	fd = open(line, O_RDONLY);
	line[space_location] = oldchar;
	if (fd)
	{
		cmd->prev->type = 0;
		line[ft_strlcpy(line, line + space_location, ft_strlen(line))] = 0;
		temp = ft_strjoin(cmd->prev->line, line);
		free(cmd->prev->line);
		cmd->prev->line = temp;
		cmd__delinvalid(cmdhead, cmd);
	}	
	close(fd);
	
	return (line);
}


// 1. meerdere argumenten
// 2. arg[0] moet bestaan.
// 3. zet vorige flag op 0 en move alles naar voren


void verify_nodes(t_node *node, t_node *nodehead)
{
	t_cmd *cmd;

	while (node)
	{
		cmd = node->cmd;
		while (cmd)
		{
			if (cmd->line[0] == 0)
				cmd__delinvalid(nodehead->cmd, cmd);
			else if (cmd->prev && cmd->prev->type != PIPE)
				cmd->line = check_arguments(nodehead->cmd, cmd, cmd->line);
			cmd = cmd->next;
		}
		node = node->next;
	}
}

void print_nodes(t_node *node, t_node *nodehead)
{
	t_cmd *cmd;

	int fd = open("/dev/ttys003", O_RDWR);
	while (node)
	{
		cmd = node->cmd;
		while (cmd)
		{
			dprintf(fd, "\x1B[32m%p - string = [%c][%s]\n\x1B[0m", node, cmd->type, cmd->line);
			cmd = cmd->next;
		}
		node = node->next;
	}	
	dprintf(fd, "\n\n\n\n\n\n\n\n");
}
//export PATH=/Users/bdekonin/minishell/noperm
