/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   findflags.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 16:15:56 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/02 11:35:48 by bdekonin      ########   odam.nl         */
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


int main(void)
{
	t_node *node;
	t_cmd *cmd1;
	t_cmd *cmd2;


	cmd1 = cmd__ft_lstnew('|', ft_strdup("cd .."));
	ft_printf("tester\n");
	cmd2 = cmd__ft_lstnew(0, ft_strdup(""));
	ft_printf("tester2\n");
	cmd__ft_lstadd_back(&cmd1, cmd2);
	ft_printf("tester3\n");
	

	if (cmd__ft_lstlast(cmd1)->line[0] == 0)
		ft_printf("EMPTY\n");

	t_cmd *test = cmd__ft_lstlast(cmd1);
	ft_printf("test = %p\n", &test);

	t_cmd *cmd = cmd1;

		while (cmd)
		{
			ft_printf("%p - string = [%c][%s]\n", &node, cmd->type, cmd->line);
			cmd = cmd->next;
		}
}