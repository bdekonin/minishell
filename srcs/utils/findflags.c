/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   findflags.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 16:15:56 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/22 09:34:16 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static void	skip_quotations(char *str, char type, int *i)
{
	while (str[*i])
	{
		if (str[*i] == type)
		{
			*i += 1;
			return ;
		}
		*i += 1;
	}
}

int			findflag(char *str, char *flags)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == '\"' || str[i] == '\'')
			skip_quotations(str, str[i], &i);
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
