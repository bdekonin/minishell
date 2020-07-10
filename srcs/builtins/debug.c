/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 20:35:14 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/10 11:22:39 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

/*
** Makes usable array for leaks
**
** @param  N/A
**
** @return char **		{leaks},
**						{minishell},
**						{NULL}
*/

// static char				**make_param(char *ppid)
// {
// 	char **arr;

// 	arr = malloc(sizeof(char*) * 3);
// 	if (!arr)
// 		return (NULL);
// 	arr[0] = ft_strdup("leaks");
// 	if (!arr[0])
// 	{
// 		ft_free_array((void*)arr, 1);
// 		return (NULL);
// 	}
// 	arr[1] = ft_strdup(ppid);
// 	if (!arr[1])
// 	{
// 		ft_free_array((void*)arr, 2);
// 		return (NULL);
// 	}
// 	arr[2] = NULL;
// 	return (arr);
// }

// /*
// ** Uses ft_execve to launch the leaks binary file.
// **
// ** @param  t_vars *v		vars
// **
// ** @return int				0 = correct
// */

// // int				leaks(t_vars *v, t_node *node, char **ret)
// // {
// // 	char **arr;

// // 	arr = make_param(v->__parentpid);
// // 	if (!arr)
// // 		return (1);
// // 	ft_execve(v, node, arr, ret);
// // 	ft_free_array((void*)arr, 3);
// // 	ft_printf("\n");
// // 	free(*ret);
// // 	return (0);
// // }

// /*
// ** Prints out the history of Lines Commands and Outputs.
// **
// ** @param  t_vars *v		vars
// **
// ** @return int				0 = correct
// */

static int				his(t_vars *v)
{
	t_history *his;

	his = v->history_head;
	ft_printf("---- History list ----\tFull\t\t\t\tRet\n");
	while (his)
	{
		ft_printf("[%s]\t\t\t\t[%s]\n", his->fullcommand, his->ret);
		his = his->next;
	}
	return (0);
}




// int				dir(t_vars *v) // will be used to check if PATH 
// {
// 	DIR *d;
// 	struct dirent *dir;

// 	d = opendir(".");
// 	if (d)
// 	{
// 		while ((dir = readdir(d)) != NULL)
// 		{
// 			printf("%s\n", dir->d_name);
// 		}
// 		closedir(d);
// 	}
// 	return (0);
// 	(void)(v);
// }

// // int				nodes(t_vars *v)
// // {
// // 	t_node *node;
// // 	t_cmd *cmd;

// // 	node = v->nodehead;
// // 	ft_printf("---- Nodes list ----\n");
// // 	while (node)
// // 	{
// // 		cmd = node->cmd;
// // 		while (cmd)
// // 		{
// // 			ft_printf("%p - string = [%c][%s]\n", node, cmd->type, cmd->line);
// // 			cmd = cmd->next;
// // 		}
// // 		ft_printf("\n");
// // 		node = node->next;
// // 	}

// // 	return (0);
// // }

/*
** Shows importent information such as, current pids & leaks & history
**
** @param  t_vars *v		vars
** @param  char **params	all the arguments after the command
**
** @return int				1 = correct \
**							0 = invalid argument \
**							-1 = malloc fail
*/

int						debug(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	int error;

	error = 0;
	// if ((params[0] && !ft_strncmp(params[0], "leaks", 7)) || !params[0])
	// 	error += leaks(v, node, ret);
	if ((params[0] && !ft_strncmp(params[0], "his", 4)) || !params[0])
		error += his(v);
	// if ((params[0] && !ft_strncmp(params[0], "nodes", 9)) || !params[0])
	// 	error += nodes(v);
	// if ((params[0] && !ft_strncmp(params[0], "dir", 4)) || !params[0])
	// 	error += dir(v);
	*ret = (error) ? ft_strdup("0") : ft_strdup("1");
	if (!*ret)
		return (0);
	(void)(v);
	(void)(cmd);
	(void)(params);
	return (1);
}
