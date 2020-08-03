/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 11:14:10 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/08/03 13:02:07 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void tester(t_cmd *cmd)
{
	char *temp;
	size_t length;
	temp = ft_calloc(PATH_MAX * 2, sizeof(char));


	ft_strcat(temp, cmd->line);
	cmd = cmd->next;
	while (cmd)
	{
		if (ft_wordcount(cmd->line) > 1)
		{
			ft_printf("strchr: '%s'\n", ft_strchr(cmd->line, 32));
			ft_strcat(temp, ft_strchr(cmd->line, 32));
		}
		else if (cmd->type && ft_wordcount(cmd->line) != 1)
			ft_strcat(temp, cmd->line);
		cmd = cmd->next;
	}
	ft_printf("temp: '%s'\n", temp);
	
	ft_printf("\nExiting\n");
	exit(1);
}

// cat export_text.txt > output Makefile
// cat export_text.txt > output Makefile Makefile
// cat < test.c
// echo "HALLO\n\n\n" > test > output > output > output