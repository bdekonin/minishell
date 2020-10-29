/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 19:05:00 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/29 17:11:49 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	handleLocations(t_vars *v, char **newpath, char **params);

int	validate_file(char *filepath)
{
	struct stat	sb;
	int			ret;
	ret = stat(filepath, &sb);
	if (ret == 0)
	{
		if (sb.st_mode & S_IXUSR)
			return (FILEFOUND);
		else
			return (FILENOTFOUND);
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
	if (!ft_strncmp(params[0], "./", 2) | !ft_strncmp(params[0], "/", 1))
		ret = get_relative_path(v, &path, params);
	else
		ret = handleLocations(v, &path, params);

	if (ret == FILEERROR)
		ft_exit_error(v, EXIT_FAILURE);
	else if (ret == FILENOTFOUND)
		return (FILENOTFOUND);


	envp = env_list_to_array(v);
	if (!envp)
	{
		free(path);
		ft_exit_error(v, EXIT_FAILURE);
	}
	ret = validate_file(path);
	if (ret == FILENOTFOUND || ret == FILEPERMISSIONS)
	{
		free(path);
		if (ret == FILEPERMISSIONS)
			ft_putendl_fd("minishell: No such file orr directory", 2);
		return (ret);
	}
	
	// printf(" -- Debug -- \n\n");
	// printf("Command = [%s]\n", params[0]);
	// printf("Path = [%d] - [%s]\n", ret, path);
	// printf("\n______params______\n");
	// ft_print_array(params);
	
	// Start
	signal(SIGQUIT, signal_exec);
	signal(SIGINT, signal_exec);
	forky = fork();
	if (!forky)
	{
		if (execve(path, &params[0], envp) < 0)
		{
			dprintf(STDERR_FILENO, "%s: %s\n", "minishell", strerror(errno));
			exit(127);
		}
	}
	else
		wait(&stat);
	// End

	ft_free_array((void **)envp, ft_lstsize(v->env));
	free(path);
	return (WEXITSTATUS(stat));
}













int		ft_execvee(t_vars *v, char **params)
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
			exit(127);
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
