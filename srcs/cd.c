/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 22:58:42 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/01 21:50:03 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void		updatecurrent_path(t_vars *v)
{
	v->current_path = getcwd(v->current_path, path_max);
}

// Version 2.0
int				cd(t_vars *v, char **params)
{
	int k = amountofsplits(v, params);
	if (k >= 1 && params[1] && \
	params[1][ft_strlen(params[1]) - 1] == 92)
		removespace(v, params + 1);
	if ((k >= 2 && !v->ptr && ft_strncmp(params[2], ";", 4)) ||
	(k >= 3 && v->ptr && ft_strncmp(params[3], ";", 4)))
	{
		errno = 7;
		perror(error);
		exit(EXIT_FAILURE);
	}
	if (!params[1] && chdir("/Users/bdekonin") < 0)
		perror(error);
	else if (chdir(params[1]) == -1)
		perror(error);
	updatecurrent_path(v);
	if (k >= 2 && !ft_strncmp(params[2], ";", 3))
		cmd(v, params + 3);
	else if (k >= 3 && !ft_strncmp(params[3], ";", 3))
		cmd(v, params + 4);
	return (1);
}
// cd srcs ; cd ..
// argv[0] = [cd]   [cd]
// argv[1] = [srcs] [srcs]
// argv[2] = [;]    [;]
// argv[3] = [cd]   [cd]
// argv[4] = [..]   [..]

// cd Test\ ing/ ; cd ..
// argv[0] = [cd]          [cd]
// argv[1] = [Test\ ing]   [Test\ ing]
// argv[2] = [^^^^]        [^^^^]
// argv[3] = [;]           [;]
// argv[4] = [cd]          [cd]
// argv[5] = [..]          [..]