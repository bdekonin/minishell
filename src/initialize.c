/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/07 11:45:55 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/11/26 21:59:56 by bdekonin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void addenv(t_vars *v, char *name, char *content)
{
	t_env *node;

	node = env__ft_lstnew(name, content);
	malloc_check(v, node);
	env__ft_lstadd_back(&v->env, node);
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
		malloc_check(v, temp);
		name = ft_substr(envp[i], 0, (size_t)(temp - envp[i]));
		malloc_check(v, name);
		content = ft_substr(temp, 1, ft_strlen(temp + 1));
		malloc_check(v, content);
		addenv(v, name, content);
		i++;
	}
}

void		initialize(t_vars *v, char **envp, char **cli)
{
	t_env *node;

	*cli = NULL;
	ft_bzero(v, sizeof(t_vars));
	v->current_path = ft_calloc(PATH_MAX + 1, sizeof(char));
		malloc_check(v, v->current_path);
	v->current_path = getcwd(v->current_path, PATH_MAX);
	create_env_list(v, envp);
	node = find_env(v, "TESTING", 0);
	if (node)
	{
		free(node->content);
		// node->content = ft_strxjoin(v->current_path, "/", MINISHELL, NULL);
		node->content = ft_strdup(MINISHELL);
		malloc_check(v, node->content);
	}
}
