/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   removespace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:47:30 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/05/15 22:49:32 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static char		*movestring(char *line)
{
	char	*temp;
	int		i;
	int		j;
	int		wc;

	i = 0;
	j = 0;
	wc = ft_wordcount(line);
	while (j < wc - 1)
	{
		temp = ft_strchr(line, 92);
		while (temp[i + 1] != '\0')
		{
			temp[i] = temp[i + 1];
			i++;
		}
		i = 0;
		j++;
	}
	temp = ft_strchr(line, '/');
	*temp = '\0';
	return (line);
}

void removespace(t_vars *v, char **argv)
{
	v->ptr = argv[0];
	while (argv[1] != NULL && (argv[1][ft_strlen(argv[1]) - 1] == 92 ||
	argv[1][ft_strlen(argv[1]) - 1] == 47) && argv[1][0] != ';')
	{
		v->ptr = ft_strjoin_trip(v->ptr, " ", argv[1]);
		if (argv[1][ft_strlen(argv[1]) - 1] == 47)
		{
			ft_memset(argv[1], strjoin_filler, ft_strlen(argv[1]));
			break ;
		}
		ft_memset(argv[0], strjoin_filler, ft_strlen(argv[0]));
		ft_memset(argv[1], strjoin_filler, ft_strlen(argv[1]));
		argv++;
	}
	free(argv[1]);
	v->argv[1] = v->ptr;
	v->argv[1] = movestring(v->argv[1]);
}