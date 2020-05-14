/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/12 15:37:50 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/12 15:37:53 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int					cd(t_vars *v, char **params)
{
	int ret_abs;

	ret_abs = ft_abs(ft_wordcount(v->line) - v->argc);
	if (ret_abs > 1 && params[1][ft_strlen(params[1]) - 1] == 92)
		removespace(v, params + 1);
	if ((ret_abs > 2 && !v->ptr && ft_strncmp(params[2], ";", 4)) ||
	(ret_abs > 3 && v->ptr && ft_strncmp(params[3], ";", 4)))
	{
		errno = 7;
		perror(error);
		exit(EXIT_FAILURE);
	}
	else if (ret_abs == 1)
	{
		if (chdir("/Users/bdekonin") < 0)
			perror(error);
	}
	else if (chdir(params[1]) == -1)
		perror(error);
	v->current_path = getcwd(v->current_path, path_max);
	if (ret_abs >= 3 && !ft_strncmp(params[2], ";", 3))
	{
		v->argc += 3;
		cmd(v, params + 3);
	}
	else if (ret_abs >= 4 && !ft_strncmp(params[3], ";", 3))
	{
		v->argc += 4;
		cmd(v, params + 4);
	}
	return (1);
}

// [Cd] [hallo] [kees] [;] [export]
//  ˆ
// [Cd] [hallo] [kees] [;] [export]
//         ˆ                           