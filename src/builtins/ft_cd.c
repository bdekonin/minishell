/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 22:54:51 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/11/25 13:16:55 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline int	exist(t_vars *v, char *string)
{
	t_env	*node;

	node = find_env(v, string, 0);
	if (node == NULL)
	{
		ft_putstr_fd(MINISHELL, 2);
		ft_putstr_fd(": cd: ", 2);
		ft_putstr_fd(string, 2);
		ft_putendl_fd(" not set", 2);
		return (-2);
	}
	else
	{
		if (!ft_strncmp("OLDPWD", string, 7))
			ft_putendl_fd(node->content, 2);
		return (chdir(node->content));
	}
}

static int			run_chdirs(t_vars *v, char **argument)
{
	int			ret;

	ret = 0;
	if (!*argument || !ft_strncmp(*argument, "--", 3) || \
			!ft_strncmp(*argument, "~", 2))
		ret = exist(v, "HOME");
	else if (!ft_strncmp(*argument, "-", 2))
		ret = exist(v, "OLDPWD");
	else
		ret = chdir(*argument);
	return (ret);
}

static void			fixoldpwdyo(t_vars *v, int ret)
{
	t_env	*pointer;

	pointer = find_env(v, "OLDPWD", 0);
	if (pointer == NULL)
		create_new_env_var(v, ft_strdup("OLDPWD"), \
			ft_strdup(v->current_path), 1);
	else if (ret == 0)
	{
		free(pointer->content);
		pointer->content = ft_strdup(v->current_path);
		malloc_check(v, pointer->content);
	}
	return ;
}

static inline int	printerror(char *argument, int ret)
{
	ft_putstr_fd(MINISHELL, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(argument, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (ret);
}

int					ft_cd(t_vars *v, char **params)
{
	int			ret_chdir;

	ret_chdir = run_chdirs(v, params);
	if (ret_chdir == -1 && ft_iserrno(ENOMEM))
		ft_exit_error(v, EXIT_FAILURE, 1);
	else if (ret_chdir == -1)
		return (printerror(params[0], 1));
	else if (ret_chdir == -2)
		return (1);
	fixoldpwdyo(v, ret_chdir);
	v->current_path = getcwd(v->current_path, PATH_MAX);
	malloc_check(v, v->current_path);
	return (0);
}

// cd kaas ; echo $?
// cd src ; echo $?
// cd ; echo $?
// cd - ; echo $?
// cd | cd ; echo $?
// cd kaas | cd ; echo $?
// cd | cd kaas ; echo $?


