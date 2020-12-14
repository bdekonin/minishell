/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 19:05:00 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/12/08 14:25:03 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int			validate_file(char *filepath)
{
	struct stat	sb;
	int			ret;
	int			returnstat;

	ret = stat(filepath, &sb);
	if (ret == 0)
	{
		returnstat = sb.st_mode & S_IXUSR;
		if (returnstat == 0)
			return (FILEPERMISSIONS);
		else
			return (FILEFOUND);
	}
	else
		return (FILENOTFOUND);
}

void		signal_exec(int sig)
{
	ft_putendl_fd("", 1);
	signal(sig, signal_exec);
}

static int	run_execve(t_vars *v, char *path, char **params, char **envp)
{
	pid_t	forky;
	int		stat;

	signal(SIGQUIT, signal_exec);
	signal(SIGINT, signal_exec);
	forky = fork();
	if (forky < 0)
		ft_exit_error(v, EXIT_FAILURE, 1);
	if (!forky)
	{
		if (execve(path, &params[0], envp) < 0)
		{
			ft_putstr_fd(MINISHELL, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			exit(127);
		}
	}
	else
		waitpid(forky, &stat, 0);
	return (WEXITSTATUS(stat));
}

static void	freething(t_vars *v, char **envp, char *path)
{
	if (!envp)
	{
		free(path);
		ft_exit_error(v, EXIT_FAILURE, 1);
	}
}

int			ft_execve(t_vars *v, \
	char **params, char *path, char *backup_command)
{
	char	**envp;
	int		ret;

	if (!ft_strncmp(backup_command, "./", 2))
	{
		ret = handle_relative(v, &path, backup_command);
		if (ret == FILEPERMISSIONS || ret == FILENOTFOUND)
			return (ret);
	}
	else
	{
		ret = handle_static(v, &path, backup_command);
		if (ret == FILEPERMISSIONS)
			return (ret);
		else if (ret == FILENOTFOUND)
			return (FILENOTFOUND * 10);
	}
	envp = env_list_to_array(v);
	freething(v, envp, path);
	ret = run_execve(v, path, params, envp);
	free(path);
	ft_free_array((void **)envp, env__ft_lstsize(v->env));
	return (ret);
}
