/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 22:58:42 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/04/29 15:31:33 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <errno.h>

static char		*movestring(t_vars *v)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strrchr(v->ptr, 92);
	while (temp[i + 1] != '\0')
	{
		temp[i] = temp[i + 1];
		i++;
	}
	temp[i] = '\0';
	return (NULL);
}

static void		updatepath(t_vars *v)
{
	v->current_path = getcwd(v->current_path, path_max);
}

void			cd(t_vars *v)
{
	v->ptr = NULL;
	if (ft_wordcount(v->line) > 2 && \
	v->argv[1][ft_strlen(v->argv[1]) - 1] == 92)
		removespace(v, v->argv + 1);
	if (v->ptr && ft_wordcount(v->line) > 2)
	{
		printf("%s - %s\n", v->ptr, v->argv[1]);
		movestring(v);
		if (v->ptr && chdir(v->ptr) == -1)
			perror("ERROR\n");
	}
	else
	{
		if (chdir(v->argv[1]) == -1)
			perror("ERROR");
	}
	updatepath(v);
}