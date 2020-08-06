/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 19:35:49 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/07/01 00:00:30 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_csearch(char c, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strsearchh(const char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s2[j] != '\0')
		{
			if (s1[i] == s2[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	free_struct(t_list *flags)
{
	free(flags);
	return (0);
}
