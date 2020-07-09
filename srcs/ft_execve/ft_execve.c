/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execve.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 14:50:11 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/09 19:33:40 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <time.h>

/*
** https://tldp.org/LDP/abs/html/exitcodes.html
*/

/*
** main.c
** chmod:                 420
** regular file
**
** minishell && kaas
** chmod:                 493
** regular file
** https://stackoverflow.com/questions/2605130/redirecting-exec-output-to-a-buffer-or-file
**
**
**
*/


// mkdir "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012346890123456789012345678901234567890"





/*
** Converts the linked list environ to a array of strings. Terminated by NULL.
**
** @param  t_vars v		vars
** @param  char **envp	array which will be filled.
** @param  t_end *head	Pointer to first argument of environ linked list.
**
** @return char **		envp (filled)
*/

static char			**__linkedlist_to_array(t_vars *v, char **envp, t_env *head)
{
	int			i;
	size_t		size;
	size_t		length;

	i = 0;
	size = env__ft_lstsize(v->env_head);
	envp = ft_calloc(size + 1, sizeof(char*));
	if (!envp)
		return (NULL);
	while (head)
	{
		length = ft_strlen(head->name) + 2 + ft_strlen(head->content);
		envp[i] = ft_calloc(length, sizeof(char));
		if (!envp[i])
		{
			ft_free_array((void*)envp, i - 1);
			return (NULL);
		}
		ft_strcat(envp[i], head->name);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], head->content);
		head = head->next;
		i++;
	}
	return (envp);
}

/*
** Executes binary/executable based on arguments
**
** @param  t_vars v			vars
** @param  char *path		path of executable e.g. -> "/usr/bin/leaks"
** @param  char **params	parameters of input e.g. ↓ (Has to be NULL terminated)
**													{leaks},
**													{minishell},
**													{NULL}
**
** @return char **			envp (filled)
*/

/*
**	Finished	1 - (....)
**	Not found	0 - (null)
**	Error	   -1 - (null)
*/
int					ft_execve(t_vars *v, t_cmd *cmd, char **params, char **ret)
{
	char *path;
	char **envp;
	int ii;
	int stat;
	
	path = NULL;
	ii = find_executable(v, &path, params[0]);
	if (ii < 0)
		return (-1);
	else if (ii == 0)
		return (0);
	envp = NULL;
	envp = __linkedlist_to_array(v, envp, v->env_head); // return or parameter not both bitch
	if (!envp)
		return (-1);
	pid_t	spoon = fork();
	if (!spoon)
	{
		signal(SIGINT, SIG_DFL); // ctrl c - for cat so you can quit
		signal(SIGTSTP, SIG_DFL); // ctrl z
		if (execve(path, "Testter", envp) < 0)
		{
			printf("ERROR1\n");
			errno = ENOEXEC;
			kill(spoon, SIGUSR1);
			exit(COMMAND_NOT_RUNNABLE);
			// free(path);
			// ft_free_array((void*)envp, env__ft_lstsize(v->env_head));
			// return (-1);
		}
	}
	// pid_t w = waitpid(spoon, &stat, WUNTRACED | WCONTINUED);
	wait(&stat);
	// wait(&stat);
	ft_free_array((void*)envp, env__ft_lstsize(v->env_head) + 1);
	free(path);

	if (errno == ENOEXEC && WEXITSTATUS(stat) == 127)
		printf("IN HEREEEE\n");
	*ret = ft_itoa(WEXITSTATUS(stat));

	if (WIFEXITED(stat))
	{
		printf("exited, status=%d\n", WEXITSTATUS(stat));
	}
	else if (WIFSIGNALED(stat))
	{
		printf("killed by signal %d\n", WTERMSIG(stat));
	}
	else if (WIFSTOPPED(stat))
	{
		printf("stopped by signal %d\n", WSTOPSIG(stat));
	}
	else if (WIFCONTINUED(stat))
	{
		printf("continued\n");
	}
	printf("WEXITSTATUS(stat) = %s\n", *ret);
	if (!*ret)
		return (0);
	return (1);
	(void)(cmd);

}