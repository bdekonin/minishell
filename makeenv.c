/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   makeenv.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 13:48:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/21 17:50:37 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline int	env__oldpwd(t_vars *v, t_env *env)
{
	char *temp;

	temp = ft_calloc(PATH_MAX, sizeof(char));
	if (!temp)
		return (0);
	ft_strlcpy(temp, env->content, ft_strlen(env->content));
	free(env->content);
	env->content = temp;
	v->__oldpwd = env;
	return (1);
}

static inline int	env__missing(t_env *head, t_env **env, \
									char *name, char *content)
{
	ft_printf(ENVIRONMENT_VAR_MISSING, name, content);
	name = ft_strdup(name);
	if (!name)
		return (0);
	content = ft_strdup(content);
	if (!content)
	{
		free(name);
		return (0);
	}
	*env = env__ft_lstnew(name, content);
	if (!*env)
	{
		free(name);
		free(content);
		return (0);
	}
	env__ft_lstadd_back(&head, *env);
	return (1);
}

static int			verify_enviroment_vars(t_vars *v, t_env *env, int ret)
{
	while (env)
	{
		if (!ft_strcmp("LOGNAME", env->name))
			v->__logname = env;
		else if (!ft_strcmp("HOME", env->name))
			v->__homedir = env;
		else if (!ft_strcmp("OLDPWD", env->name))
		{
			if (!env__oldpwd(v, env))
				return (0);
		}
		else if (!ft_strcmp("PATH", env->name))
			v->__path = env;
		else if (!ft_strcmp("SHELLNAME", env->name))
			v->__executable = env;
		env = env->next;
	}
	if (ret && !v->__logname)
		ret = env__missing(v->env_head, &v->__logname, "LOGNAME", MISSING_LOGNAME);
	if (ret && !v->__homedir)
		ret = env__missing(v->env_head, &v->__homedir, "HOME", v->current_path);
	if (ret && !v->__executable)
		ret = env__missing(v->env_head, &v->__executable, "SHELLNAME", MISSING_SHELLNAME);
	return (ret);
}

static void			env__makelist_loop(t_vars *v, char *name, char *content)
{
	t_env *env;

	env = env__ft_lstnew(name, content);
	if (!env)
	{
		free(name);
		free(content);
		ft_exit_error(v, EXIT_FAILURE);
	}
	if (!v->env_head)
		v->env_head = env;
	else
		env__ft_lstadd_back(&v->env_head, env);
}

int					env__makelist(t_vars *v, char **envp)
{
	char	*name;
	char	*content;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i])
	{
		temp = ft_strchr(envp[i], '=');
		name = ft_substr(envp[i], 0, (int)(temp - envp[i]));
		if (!name)
			ft_exit_error(v, EXIT_FAILURE);
		content = ft_substr(temp, 1, ft_strlen(temp));
		if (!content)
		{
			free(name);
			ft_exit_error(v, EXIT_FAILURE);
		}
		env__makelist_loop(v, name, content);
		i++;
	}
	verify_enviroment_vars(v, v->env_head, 1);
	return (1);
}
