/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:33:04 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/07/20 08:27:54 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int check_newline_option(char *param)
{
	if (!ft_strncmp(param, "-n", 3))
		return (1);
	return (0);
}

static int do_dollar_mark(t_vars *v, char *str, size_t *i)
{
	size_t len;
	char *env_name;
	char *env_content;

	*i += 1;
	len = 0;
	while (str[*i + len] != '\0' && str[*i + len] != '\"' && str[*i + len] != ' ')
		len++;
	//printf("len=[%lu]\n", len); //debug
	if (len == 0)
		return (0);
	env_name = str + *i;
	//printf("name=[%s]\n", env_name); //debug
	env_content = find_environment_variable(v, env_name);
	//printf("cont=[%s]\n", env_content); //debug
	if (!env_content)
		return (0);
	write(1, env_content, ft_strlen(env_content)); //protect
	*i += len;
	return (1);
}

static int do_double_quote(t_vars *v, char *str, size_t *i)
{
	*i += 1;
	while (str[*i] != '\0' && str[*i] != '\"')
	{
		if (str[*i] == '$')
		{
			if (do_dollar_mark(v, str, i) != 1)
				return (0);
		}
		else
		{
			write(1, str + *i, 1); //protect?
			*i += 1;
		}
	}
	return (1);
}

static int do_single_quote(char *str, size_t *i)
{
	*i += 1;
	while (str[*i] != '\0' && str[*i] != '\'')
	{
		write(1, str + *i, 1); //protect?
		*i += 1;
	}
	return (1);
}

static int do_comment_mark(char *str, size_t *i)
{
	*i += 1;
	while (str[*i] != '\0')
		*i += 1;
	return (*i);
	//return (ft_strlen(str + *i));
}

static int do_something(char *str, size_t *i)
{
	*i += 1;
	write(1, str + *i, 1); //prot
	return (1);
}

static int print_strings(t_vars *v, char *str)
{
	size_t	i;
	int	ret;

	if (!v)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
			ret = do_something(str, &i);
		else if (str[i] == '\'')
			ret = do_single_quote(str, &i);
		else if (str[i] == '\"')
			ret = do_double_quote(v, str, &i);
		else if (str[i] == '$')
			ret = do_dollar_mark(v, str, &i);
		else if (str[i] == '#')
			ret = do_comment_mark(str, &i);
		else
			ret = write(1, str + i, 1);
		if (ret < 1)
			return (ret);
		i++;
	}
	return (1);
}

int echo(t_vars *v, t_cmd *cmd, char **params)
{
	size_t size;
	size_t i;
	int newline_opt;
	int ret;
	
	newline_opt = check_newline_option(params[0]);
	i = newline_opt;
	size = 0;
	params = ft_split_sep_exep(cmd->line, " ", &size);
	if (!params)
		return (0); //malloc
	params = params + 1; //delete this when arg char **params is correct
	// int j = 0; //debug
	// while (params[j]) //debug
	// {
	// 	printf("params[%d] = [%s]\n", j, params[j]);
	// 	j++;
	// }
	while (params[i] && i < size)
	{
		ret = print_strings(v, params[i]);
		if (ret == 1 && i < size)
			write(1, " ", 1);
		else if (ret < 0)
			return (0); //error
		i++;
	}
	if (!newline_opt && write(1, "\n", 1) != 1)
		return (1);
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}
