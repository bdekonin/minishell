/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iserrno_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 16:12:20 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/10/09 22:33:51 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

int		ft_iserrno(int error)
{
	if (errno == error)
		return (1);
	else
		return (0);
}
