/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   removespace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:47:30 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/28 16:43:34 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void removespace(t_vars *v, char **argv)
{
	v->ptr = argv[0];
	while (argv[1] != NULL && (argv[1][ft_strlen(argv[1]) - 1] == 92 ||
	argv[1][ft_strlen(argv[1]) - 1] == 47) && argv[1][0] != ';')
	{
		v->ptr = ft_strjoin(v->ptr, " ", argv[1]);
		if (argv[1][ft_strlen(argv[1]) - 1] == 47)
		{
			ft_memset(argv[1], strjoin_filler, ft_strlen(argv[1]));
			break ;
		}
		// Sets characters to value. So the program knows it has been read and copied.
		ft_memset(argv[0], strjoin_filler, ft_strlen(argv[0]));
		ft_memset(argv[1], strjoin_filler, ft_strlen(argv[1]));
		argv++;
	}
}