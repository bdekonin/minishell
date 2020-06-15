/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   findflags.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 16:15:56 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/06/15 16:16:17 by bdekonin      ########   odam.nl         */
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
