/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   findflags.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 16:15:56 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/02 23:08:32 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int findflag(char *str, char *flags)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (flags[j])
		{
			if (flags[j] == str[i])
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}


// static void tester(void)
// {
// 		t_cmd *cmd;
// 	t_cmd *cmd2;

// 	cmd = cmd__ft_lstnew(0, ft_strdup("first"));
// 	cmd2 = cmd__ft_lstnew(0, ft_strdup("second"));
// 	cmd__ft_lstadd_back(&cmd, cmd2);

// 	cmd2 = cmd__ft_lstnew(0, ft_strdup("third"));	
// 	cmd__ft_lstadd_back(&cmd, cmd2);
	
// 	cmd2 = cmd__ft_lstnew(0, ft_strdup("fourth"));
// 	cmd__ft_lstadd_back(&cmd, cmd2);
// 	t_cmd *test;
// 	test = cmd;
// 	while (test)
// 	{
// 		ft_printf("++ %s\n", test->line);
// 		test = test->next;
// 	}
// 	test = cmd__ft_lstlast(cmd);
// 	while (test)
// 	{		
// 		ft_printf("-- %s\n", test->line);
// 		test = test->prev;	
// 	}
// 	t_node *node;
	
// 	node = node__ft_lstnew(&cmd)
// }


// int main(void)
// {
// 	tester();
// 	system("leaks minishell");
// }