/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   amountofsplits.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/01 20:57:44 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/01 20:58:12 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int amountofsplits(t_vars *v, char **params)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (ft_strncmp(params[i], v->argv[ft_wordcount(v->line) - 1], ft_strlen(v->line)))
	{
		if (!ft_strncmp(params[i], ";", 3))
			return (i);
		i++;
	}
	return (i);
}
