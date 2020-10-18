/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/07 11:45:55 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/15 15:37:01 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			env__missing(t_vars *v, char *name, char *content)
{
	ft_printf(ENVIRONMENT_VAR_MISSING, name, content);
	name = ft_strdup(name);
	if (!name)
		ft_exit_error(v, EXIT_FAILURE);
	content = ft_strdup(content);
	if (!content)
		ft_exit_error(v, EXIT_FAILURE);
	create_new_env_var(v, name, content);
}

static void			env__oldpwd(t_vars *v, t_env *env)
{
	char *temp;

	temp = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!temp)
		ft_exit_error(v, EXIT_FAILURE);
	ft_strlcpy(temp, env->content, ft_strlen(temp) + 1);
	free(env->content);
	env->content = temp;
	//v->default_oldpwd->content = env->content;
}

static void			verify_environment_vars(t_vars *v, t_list *lst, int ret)
{
	t_env *tmp;

	while (lst)
	{
		tmp = lst->content;
		if (!tmp->name)
		{
			lst = lst->next;
			continue ;
		}
		else if (!ft_strcmp("HOME", tmp->name))
			v->default_homedir = tmp;
		else if (!ft_strcmp("OLDPWD", tmp->name))
			env__oldpwd(v, tmp);
		else if (!ft_strcmp("PATH", tmp->name))
			v->default_path = tmp;
		lst = lst->next;
	}
	if (ret && !v->default_homedir)
		env__missing(v, "HOME", v->current_path);
}

static void	create_env_list(t_vars *v, char **envp)
{
	char	*name;
	char	*content;
	char	*temp;
	size_t	i;
	
	i = 0;
	while (envp[i] != NULL)
	{
		temp = ft_strchr(envp[i], '=');
		if (!temp)
			ft_exit_error(v, EXIT_FAILURE);
		name = ft_substr(envp[i], 0, (size_t)(temp - envp[i]));
		if (!name)
			ft_exit_error(v, EXIT_FAILURE);
		content = ft_substr(temp, 1, ft_strlen(temp + 1));
		if (!content)
			ft_exit_error(v, EXIT_FAILURE);
		create_new_env_var(v, name, content);
		i++;
	}
}

void		initialize(t_vars *v, char **envp)
{
	ft_bzero(v, sizeof(t_vars));
	v->prefix = ft_strdup(PROMPT);
	if (!v->prefix)
		ft_exit_error(v, EXIT_FAILURE);
	v->current_path = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!v->current_path)
		ft_exit_error(v, EXIT_FAILURE);
	v->current_path = getcwd(v->current_path, PATH_MAX);
	v->pipefd[0] = -1;
	v->pipefd[1] = -1;
	v->forky = 1;
	create_env_list(v, envp);
	verify_environment_vars(v, v->env, 1);
}
