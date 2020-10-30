/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 19:05:00 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/30 22:02:57 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	handleLocations(t_vars *v, char **newpath, char **params);

int	validate_file(char *filepath)
{
	struct stat	sb;
	int			ret;
	int			returnstat;
	ret = stat(filepath, &sb);
	if (ret == 0) // Exist
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

void	signal_exec(int sig)
{
	ft_putendl_fd("", 1);
	signal(sig, signal_exec);
}

int		ft_execve(t_vars *v, char **params)
{
	char *path;
	char **envp;
	pid_t forky;
	int stat;

	path = NULL;

	// Temp
	int ret = -2;
	if (!ft_strncmp(params[0], "./", 2) || !ft_strncmp(params[0], "/", 1))
	{
		ret = handle_relative(v, &path, params[0]);
		if (ret == FILEPERMISSIONS || ret == FILENOTFOUND)
			return (ret);
	}
	else
	{
		ret = handle_static(v, &path, params[0]);
		// printf("STATIC - [%d]\n", ret);
		if (ret == FILEPERMISSIONS)
			return (ret);
		else if (ret == FILENOTFOUND)
			return (FILENOTFOUND * 10);
	}
	if (ret == FILEERROR)
		ft_exit_error(v, EXIT_FAILURE);

	envp = env_list_to_array(v);
	if (!envp)
	{
		free(path);
		ft_exit_error(v, EXIT_FAILURE);
	}
	

	
	// Start
	signal(SIGQUIT, signal_exec);
	signal(SIGINT, signal_exec);
	forky = fork();
	if (!forky)
	{
		if (execve(path, &params[0], envp) < 0)
		{
			ft_printf("%s: %s\n", "minishell", strerror(errno));
			exit(127);
		}
	}
	else
		waitpid(forky, &stat, 0);
	// End



	ft_free_array((void **)envp, ft_lstsize(v->env));
	free(path);
	return (WEXITSTATUS(stat));
}


// clear ; ./test/testfunctions/return_8_noperm ; ./bestaat
// clear ; ./test/testfunctions/return_8_noperm ; echo " cmd_ret = [$?]" ; ./bestaat ; echo " cmd_ret = [$?]"
