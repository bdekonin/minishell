/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 22:58:42 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/30 20:41:52 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <errno.h>

static void		updatepath(t_vars *v)
{
	v->current_path = getcwd(v->current_path, path_max);
}

// Version 2.0
int				cd(t_vars *v, char **params)
{
	// if (ft_wordcount(v->line) > 2 && \
	// params[1][ft_strlen(params[1]) - 1] == 92)
	// 	removespace(v, params + 1);
	if (!v->argv[1])
	{
		if (chdir("/Users/bdekonin") < 0)
			perror("ERROR\n");
	}
	else if (chdir(params[1]) == -1)
		perror("ERROR\n");
	// for (int i = 0; i < ft_wordcount(v->line); i++)
	// 	ft_printf("argv[%d] = [%s]\t[%s]\n", i, params[i], v->argv[i]);
	updatepath(v);
	if (params[2] && !ft_strncmp(params[2], ";", 3))
		cmd(v, params + 3);
	else if (params[3] && !ft_strncmp(params[3], ";", 3))
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
// argv[3] = [0x]          [0x]
// argv[4] = [cd]          [cd]
// argv[5] = [..]          [..]