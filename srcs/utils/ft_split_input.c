/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 10:35:33 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/01 10:15:00 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static void printarr(char **arr, int size, char type)
{
	int i;

	i = 0;
	while (i != size)
	{
		ft_printf("arr[%i][%c] = [%s]\n", i, type, arr[i]);
		i++;
	}
}

static void initialize_arrays(int *i)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	return ;
}

/*
** [0] = ;
** [1] = |
** [2] = >
** [3] = <
** pwd1 | pwd2 > pwd3 | pwd4
*/

int ft_split_input(t_vars *v)
{
	char	*temp;
	char	**argv[4];
	size_t 	splitsize[4];
	// int		i[4];
	t_node	*node;
	t_cmd	*cmd_head;

	char **aargv = ft_split_sep(v->line, ";", &splitsize[0]);
	char *line;
	int i = 0;
	while (i < (int)splitsize[0])
	{
		while(1)
		{
			cmd_head = 
		}
		i++;
	}


	
	char *trimline;
	for (int j = 0; j < (int)splitsize[0]; j++)
	{
		trimline = ft_strtrim(aargv[j], " \t");
		if (!trimline)
			return (0); // free llist
		node__ft_lstadd_back(&v->nodehead, node__ft_lstnew(';', 0, trimline));
	}
	// if (argv[0])
	// 	ft_free_array((void*)argv[0], splitsize[0]);
	
}














// int ft_split_input(t_vars *v)
// {
// 	char	*temp;
// 	char	**argv[4];
// 	size_t 	splitsize[4];
// 	int		i[4];
// 	t_node *node;

// 	// i[0] = 0;

// 	initialize_arrays(&i);
// 	argv[0] = ft_split_sep(v->line, ";", &splitsize[0]);
// 	while (i[0] < (int)splitsize[0])
// 	{
// 		argv[1] = ft_split_sep(argv[0][i[0]], "|", &splitsize[1]);
// 		printarr(argv[1], splitsize[1], '|');
// 		// ft_printf("args[1][%d][|] = (%s)\n", i[1], argv[1][i[1]]);
// 		// ft_printf("args[1][%d][|] = (%s)\n\n", i[1] + 1, argv[1][i[1] + 1]);
// 		while (i[1] < (int)splitsize[1])
// 		{
// 		// 	argv[2] = ft_split_sep(argv[1][i[1]], ">", &splitsize[2]);
// 		// 	ft_printf("args[2][%d][>] = (%s)\n", i[2], argv[2][i[2]]);
// 		// 	ft_printf("args[2][%d][>] = (%s)\n\n", i[2] + 1, argv[2][i[2] + 1]);
// 		// 	while (i[2] < (int)splitsize[2])
// 		// 	{
// 		// 		// argv[3] = ft_split_sep(argv[2][i[2]], ">", &splitsize[3]);
// 		// 		// ft_printf("args[3][%d][>] = (%s)\n", i[3], argv[3][i[3]]);
// 		// 		// ft_printf("args[3][%d][>] = (%s)\n\n", i[3] + 1, argv[3][i[3] + 1]);
// 		// 		// while (i[3] < (int)splitsize[3])
// 		// 		// {
// 		// 		// 	i[3]++;
// 		// 		// }
// 		// 		i[2]++;
// 		// 	}
// 		// 	i[1]++;
// 		}
// 		i[0]++;
// 	}

// 	char *trimline;
// 	for (int j = 0; j < (int)splitsize[0]; j++)
// 	{
// 		trimline = ft_strtrim(argv[0][j], " \t");
// 		if (!trimline)
// 			return (0); // free llist
// 		node__ft_lstadd_back(&v->nodehead, node__ft_lstnew(';', 0, trimline));
// 	}
// 	if (argv[0])
// 		ft_free_array((void*)argv[0], splitsize[0]);
	
// }












// int ft_split_input(t_vars *v, size_t splitsize, char **argv_semicolen)
// {
// 	char *trimline;
// 	char **argv_pipe;
// 	t_node *node;

// 	for (int j = 0; j < (int)splitsize; j++)
// 	{
// 		trimline = ft_strtrim(argv_semicolen[j], " \t");
// 		if (!trimline)
// 			return (0); // free llist
// 		node__ft_lstadd_back(&v->nodehead, node__ft_lstnew(';', 0, trimline));
// 	}	
// }