/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   removespace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:47:30 by bdekonin      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/04/30 18:52:18 by bdekonin      ########   odam.nl         */
=======
/*   Updated: 2020/04/28 16:43:34 by bdekonin      ########   odam.nl         */
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

<<<<<<< HEAD
static char		*movestring(char *line)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strrchr(line, 92);
	while (temp[i + 1] != '\0')
	{
		temp[i] = temp[i + 1];
		i++;
	}
	temp[i] = '\0';
	return (line);
}

=======
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
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
<<<<<<< HEAD
	free(argv[1]);
	v->argv[1] = v->ptr;
	v->argv[1] = movestring(v->argv[1]);
=======
>>>>>>> 0ee2dea2c56e38d1e663ec688b34dc1f97df40e1
}