/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_command_line_input_more.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 15:56:31 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/05 16:12:54 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printerror(char *file, int error)
{
	ft_putstr_fd(MINISHELL, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (error == ENOENT)
		ft_putendl_fd(MINISHELL_ENOENT, 2);
	else if (error == EACCES)
		ft_putendl_fd(MINISHELL_EACCES, 2);
	else if (error == CMDERR)
		ft_putendl_fd(MINISHELL_CMDERR, 2);
}

char	*make_backup_command(t_vars *v, char *backup)
{
	malloc_check(v, backup);
	ft_str_to_lower(backup);
	v->backup_command = backup;
	return (backup);
}

void	control_d(t_vars *v, char **cli, int ret)
{
	char *tmp;

	if (!*cli[0])
		ft_exit_error(v, EXIT_SUCCESS, 1);
	tmp = ft_strdup(*cli);
	free(*cli);
	malloc_check(v, tmp);
	while (ret == 0)
	{
		*cli = NULL;
		ret = get_next_line(STDIN_FILENO, cli);
		if (ret < 0)
			ft_exit_error(v, EXIT_FAILURE, 0);
		tmp = ft_append(tmp, (*cli));
		free(*cli);
		malloc_check(v, tmp);
	}
	*cli = tmp;
}

void	split_tokens(t_vars *v, char *string)
{
	char	**tokens;
	size_t	size_tokens;

	if (string[0] == 0)
	{
		v->cmd_ret = 0;
		return ;
	}
	tokens = ft_split_multi(string, STRING_SPECIAL_CHAR, &size_tokens);
	malloc_check(v, tokens);
	v->cmd_ret = run_command(v, tokens, 0);
	ft_free_array((void **)tokens, size_tokens);
}

int		free_input_args(void **array, size_t i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
	return (1);
}
