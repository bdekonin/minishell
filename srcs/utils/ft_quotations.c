/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_quotations.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 19:55:42 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/15 20:10:32 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int ft_quotations(char **line, char type, char *prompt)
{
	int i;
	int ret_expand;
	char *temp = ft_calloc(PATH_MAX, sizeof(char));

	i = 0;
	while (*line[i])
	{
		if (*line[i] == type)
			return (1);
		if (*line[i] == '$')
			printf("DOLLAR TEKEN\n");
		temp[i] = *line[i]
	}

	ft_printf("temp-%s\n", temp);
}
