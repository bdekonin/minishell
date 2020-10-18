/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 19:05:00 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/15 18:00:06 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//printf("get_relative_path ret = [%d]-[%s]\n", ret, new_path); 	//debug
		if (ret < 0)
		{
			ft_printf("%s: %s: %s\n", "minishell", params[0], strerror(errno));
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
//		signal(SIGINT, SIG_DFL); // ctrl c - for cat so you can quit
//		signal(SIGTSTP, SIG_DFL); // ctrl z
		//printf("params=[%s]\n", params[0]);		//debug
		//printf("path=[%s]\n", new_path);			//debug
		if (execve(new_path, &params[0], envp) < 0)
		{
			ft_printf("%s: %s\n", "minishell", strerror(errno));
			exit(COMMAND_NOT_RUNNABLE);
		}
	}
	else
	{
		wait(&stat);
	}
	ft_free_array((void **)envp, ft_lstsize(v->env));
	free(new_path);
	//set_history(v);
	return (1);
}
