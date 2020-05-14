/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/01 22:36:56 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/01 22:46:15 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libft/libft.h"

int main(void)
{
	char *line = ft_strdup("Hallo wie ben jij nou weer");
	char **argv = ft_split(line, ' ');

	for(int i = 0; i < ft_wordcount(line) + 5; i++)
	{
		printf("%d - [%s]\n", i, argv[i]);
	}
}