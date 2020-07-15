/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:33:04 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/07/15 11:56:26 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int check_newline_option(char *param)
{
	int newline_opt;

	if (!ft_strncmp(param, "-n", 3))
		newline_opt = 1;
	else
		newline_opt = 0;
	return (newline_opt);
}

static char *trim_string(char *src)
{
	char *dst;
	char set[3];

	set[0] = 34;
	set[1] = 39;
	set[2] = 0;
	dst = ft_strtrim(src, set);
	// printf("src = [%s]\ndst = [%s]\n", src, dst);
	return (dst);
}

static char *find_env_var_name(t_env **head, char *param)
{
	t_env	*tmp;
	char	*str;
	
	tmp = *head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, param, ft_strlen(param)))
		{
			str = ft_strdup(tmp->content);
			return (str);
		}
		tmp = tmp->next;
	}
	return (0); //$name does not exist in env list
}

static int	print_text(t_vars *v, char ** params, int i)
{
	char	*str;
	ssize_t	write_ret;
	
	while (params[i])
	{
		if (params[i][0] == '$' && params[i][1] != ' ')
			str = find_env_var_name(&v->env_head, params[i] + 1);
		else
			str = trim_string(params[i]);
		if (!str)
			return (0);
		write_ret = write(1, str, ft_strlen(str));
		free(str);
		if (write_ret < 0 || (size_t)write_ret != ft_strlen(str))
			return (0);
		if (params[i + 1] && write (1, " ", 1) != 1)
			return (0);
		i++;
	}
	return (1);
}

int echo(t_vars *v, t_cmd *cmd, char **params)
{
	int i;
	int newline_opt;

	i = 0;
	newline_opt = check_newline_option(params[i]);
	i += newline_opt;
	if (!print_text(v, params, i))
		return (1);
	if (!newline_opt && write(1, "\n", 1) != 1)
		return (1);
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}
