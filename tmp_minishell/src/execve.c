/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 19:05:00 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/29 13:29:55 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execvee(t_vars *v, char **params)
{
	char *path;

	path = NULL;
	if (!ft_strncmp(params[0], "./", 2) | !ft_strncmp(params[0], "/", 1))
	{
		// Relative
		ft_printf("Relative\n\n");

		get_relative_path(v, &path, params);
		ft_printf("Path = [%s]\n", path);
	}
	else
	{
		// $PATH executable
		ft_printf("$PATH executable\n\n");
	}
	
	return (1);
}













int		ft_execve(t_vars *v, char **params)
{
	int		ret;
	char	*new_path;
	char	**envp;
	pid_t	spoon;
	int		stat;
	
	new_path = NULL;
	if (!ft_strncmp(params[0], "./", 2))
	{
		ret = get_relative_path(v, &new_path, params);
		if (ret < 0)
		{
			dprintf(STDERR_FILENO, "%s: %s: %s\n", "minishell", params[0], strerror(errno));
			return (ret);
		}
	}
	else
	{	
		ret = loop_locations(v, &new_path, params);
		if (ret == -1 || ret == 0)
			return (ret);
	}
	envp = env_list_to_array(v);
	if (!envp)
		return (-1);
	spoon = fork();
	if (!spoon)
	{
		if (execve(new_path, &params[0], envp) < 0)
		{
			dprintf(STDERR_FILENO, "%s: %s\n", "minishell", strerror(errno));
			exit(COMMAND_NOT_RUNNABLE);
		}
	}
	else
	{
		waitpid(spoon, &stat, 0);
	}
	ft_free_array((void **)envp, ft_lstsize(v->env));
	free(new_path);
	//set_history(v);
	return (1);
}
