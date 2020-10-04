/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/07 11:45:55 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/09/30 13:57:23 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_to_list(t_vars *v, char *name, char *content)
{
	t_list	*new;
	t_env	*node;
	
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
	{
		free(name);
		free(content);
		ft_exit_error(v, EXIT_FAILURE);
	}
	node->name = name;
	node->content = content;
	new = ft_lstnew(node);
	if (!new)
	{
		free(node->name);
		free(node->content);
		free(node);
		ft_exit_error(v, EXIT_FAILURE);
	}
	ft_lstadd_back(&v->env, new);
}

static int	env__missing(t_vars *v, char *name, char *content)
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
	add_env_to_list(v, name, content);
	return (1);
}

static int	env__oldpwd(t_vars *v, t_env *env) //wat doet deze functie? (ik snap hem niet)
{
	char *temp;

	temp = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!temp)
		return (0);
	ft_strlcpy(temp, env->content, ft_strlen(temp) + 1);
	free(env->content);
	env->content = temp;
	//v->default_oldpwd->content = env->content;
	return (1);
}

static int	env__shell(t_vars *v, t_env *env)
{
	free(env->content);
	env->content = ft_strdup(MISSING_SHELLNAME);
	if (!env->content)
		return (0);
	v->default_executable = env;
	return (1);
}

static int			verify_environment_vars(t_vars *v, t_list *lst, int ret)
{
	t_env *tmp;

	while (lst)
	{
		tmp = lst->content;
//		printf("tmp->name = [%s]\t", tmp->name);
//		printf("tmp->cont = [%s]\n", tmp->content);
		if (!tmp->name)
		{
			lst = lst->next;
			continue ;
		}
		else if (!ft_strcmp("LOGNAME", tmp->name))
			v->default_logname = tmp;
		else if (!ft_strcmp("HOME", tmp->name))
			v->default_homedir = tmp;
		else if (!ft_strcmp("OLDPWD", tmp->name))
		{
			if (!env__oldpwd(v, tmp))
				return (0);
		}
		else if (!ft_strcmp("PATH", tmp->name))
			v->default_path = tmp;
		else if (!ft_strcmp("SHELL", tmp->name) && !env__shell(v, tmp))
			return (0);
		lst = lst->next;
	}
	if (ret && !v->default_logname)
		ret = env__missing(v, "LOGNAME", MISSING_LOGNAME);
	if (ret && !v->default_homedir)
		ret = env__missing(v, "HOME", v->current_path);
	if (ret && !v->default_executable)
		ret = env__missing(v, "SHELL", MISSING_SHELLNAME);
	return (ret);
}

static void	create_env_list(t_vars *v, char **envp)
{
	char	*name;
	char	*content;
	char	*temp;
	size_t	i;
	
	i = 0;
	while (envp[i])
	{
		temp = ft_strchr(envp[i], '=');
		if (!temp)
			ft_exit_error(v, EXIT_FAILURE);
		name = ft_substr(envp[i], 0, (size_t)(temp - envp[i]));
		if (!name)
			ft_exit_error(v, EXIT_FAILURE);
		content = ft_substr(temp, 1, ft_strlen(temp + 1));
		if (!content)
		{
			free(name);
			ft_exit_error(v, EXIT_FAILURE);
		}
		add_env_to_list(v, name, content);
		i++;
	}
}

int	initialize_struct(t_vars *v, char **envp)
{
	ft_bzero(v, sizeof(t_vars));
	v->pipefd[0] = -1;
	v->pipefd[1] = -1;
	v->forky = 1;
	v->prefix = ft_strdup(PREFIX);
	if (!v->prefix)
		ft_exit_error(v, EXIT_FAILURE);
	v->current_path = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!v->current_path)
		ft_exit_error(v, EXIT_FAILURE);
	v->current_path = getcwd(v->current_path, PATH_MAX);
	create_env_list(v, envp);
	if (!verify_environment_vars(v, v->env, 1))
		ft_exit_error(v, EXIT_FAILURE);
	return (1);
}