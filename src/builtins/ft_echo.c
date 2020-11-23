/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:33:04 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/23 21:24:32 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	check_newline_option(char **params, int *newline_opt)
{
	size_t i;
	size_t j;

	*newline_opt = 0;
	i = 0;
	while (params[i] && !ft_strncmp(params[i], "-n", 2))
	{
		j = 2;
		while (params[i][j] == 'n')
			j++;
		if (params[i][j] == '\0')
			*newline_opt = 1;
		else
			return (i);
		i++;
	}
	return (i);
}

static char		*init_dst(char *param, size_t *i)
{
	char *dst;

	if (param)
	{
		dst = ft_strdup(param);
		*i += 1;
	}
	else
		dst = ft_strdup("\0");
	return (dst);
}

static void		append_to_dst(t_vars *v, char **params, char **dst, size_t i)
{
	char *tmp;

	while (params[i])
	{
		tmp = ft_strxjoin(*dst, " ", params[i], NULL);
		free(*dst);
		if (!tmp)
			ft_exit_error(v, EXIT_FAILURE, 1);
		*dst = tmp;
		i++;
	}
}

int				ft_echo(t_vars *v, char **params)
{
	ssize_t	ret;
	size_t	i;
	int		newline_opt;
	char	*dst;

	i = check_newline_option(params, &newline_opt);
	dst = init_dst(params[i], &i);
	malloc_check(v, dst);
	append_to_dst(v, params, &dst, i);
	ret = write(1, dst, ft_strlen(dst));
	free(dst);
	if (ret < 0 || (size_t)ret != ft_strlen(dst))
		ft_exit_error(v, EXIT_FAILURE, 1);
	if (newline_opt == 0 && write(1, "\n", 1) != 1)
		ft_exit_error(v, EXIT_FAILURE, 1);
	return (0);
}
