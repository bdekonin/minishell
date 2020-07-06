/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   makeenv.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 13:48:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/05 19:14:38 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int env__makelist(t_vars *v, char **envp)
{
	t_env	*env;
	char	**arr;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i])
	{
		// size_t sezeee;
		// system("leaks minishell");
		arr = ft_split(envp[i], '=');
		// // if (!arr)
		// // 	return () error
		// system("leaks minishell");
		if (i == 0)
		{
			v->env_head = env__ft_lstnew(arr[0], arr[1]);
			env = v->env_head;
		}
		else
			env = env__ft_lstnew(arr[0], arr[1]);
		// // if (!env)
		// // 	return () error
		if (!ft_strcmp("LOGNAME", arr[0]))
			v->__logname = env;
		else if (!ft_strcmp("HOME", arr[0]))
			v->__homedir = env;
		else if (!ft_strcmp("OLDPWD", arr[0]))
		{
			temp = ft_calloc(PATH_MAX ,sizeof(char));
			// // if (!temp)
			// // 	return () error
			ft_strlcpy(temp, env->content, ft_strlen(env->content));
			free(env->content);
			env->content = temp;
			v->__oldpwd = env;
		}
		// else if (!ft_strcmp("OLDPWD", arr[0]))
		if (i != 0)
			env__ft_lstadd_back(&v->env_head, env);
		free(arr[2]);
		free(arr);
		i++;
	}
	// !LOGNAME
	// !HOME
	// !OLDPWD
	// !PWD
	env = env__ft_lstlast(v->env_head);
	v->__executable = ft_strrchr(env->content, '.');
	return (1);
}


//https://stackoverflow.com/questions/40584034/when-and-why-do-i-have-to-close-pipe#:~:text=5-,dup2(pipefd%5B1%5D%2C%201)%3B%20close(pipefd,its%20own%20pipe%20file%20descriptors.
// int dup2(int oldfd, int newfd);

// int main(void)
// {
	// int pipefd[2];
	// pipe(pipefd);	

	// if (fork() == 0)
	// {
	// 	close(pipefd[0]);    // close reading end in the child	
	// 	dup2(pipefd[1], 1);  // send stdout to the pipe
	// 	dup2(pipefd[1], 2);  // send stderr to the pipe	

	// 	close(pipefd[1]);    // this descriptor is no longer needed	
	// 	system("cat srcs/utils/env_list/ft_envadd_front_bonus.c");
	// }
	// else
	// {
	// 	// parent
	// 	char *line;
	// 	close(pipefd[1]);  // close the write end of the pipe in the parent	

	// 	ft_printf("\x1B[33m");
	// 	while (get_next_line(pipefd[0], &line) > 0)
	// 	{
	// 		ft_printf("%s\n", line);
	// 		free(line);
	// 	}
	// 	ft_printf("\x1B[0m");
	// }

	// if (fork() == 0)
	// {
	// 	// child
	// 	int fd = open("kaulo", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	
	// 	dup2(fd, 1);	// make stdout go to file
	// 	dup2(fd, 2);	// make stderr go to file - you may choose to not do this
	// 					// or perhaps send stderr to another file
	
	// 	close(fd);		// fd no longer needed - the dup'ed handles are sufficient
	
	// 	system("cat srcs/utils/env_list/ft_envadd_front_bonus.c");
	// }

// }


#include <stdio.h>
#include <fcntl.h>
