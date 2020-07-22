/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:33:04 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/07/22 12:07:17 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int check_newline_option(char *param)
{
	if (!ft_strncmp(param, "-n", 3))
		return (1);
	return (0);
}

static int write_dollar_mark(t_vars *v, char *str, size_t *i)
{
	size_t len;
	char *env_name;
	char *env_content;

	*i += 1;
	len = 0;
	while (str[*i + len] != '\0' && str[*i + len] != '\"' && str[*i + len] != ' ') //see charsearch_bool in parse_cd.c
		len++;
	if (len == 0)
		return (0);
	env_name = str + *i;
	//printf("name=[%s]\n", env_name); //debug
	env_content = find_environment_variable(v, env_name, &len);
	if (!env_content)
		return (0);
	//printf("cont=[%s]\n", env_content); //debug
	write(1, env_content, ft_strlen(env_content)); //protect
	*i += len;
	return (1);
}

static int write_double_quote(t_vars *v, char *str, size_t *i)
{
	*i += 1;
	while (str[*i] != '\0' && str[*i] != '\"')
	{
		if (str[*i] == '$')
		{
			if (write_dollar_mark(v, str, i) != 1) //return func?
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

static int write_single_quote(char *str, size_t *i)
{
	*i += 1;
	while (str[*i] != '\0' && str[*i] != '\'')
	{
		write(1, str + *i, 1); //protect?
		*i += 1;
	}
	return (1);
}

static int write_comment_mark(char *str, size_t *i)
{
	*i += 1;
	while (str[*i] != '\0')
		*i += 1;
	return (1);
}

static int write_backslash(char *str, size_t *i)
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
			ret = write_backslash(str, &i);
		else if (str[i] == '\'')
			ret = write_single_quote(str, &i);
		else if (str[i] == '\"')
			ret = write_double_quote(v, str, &i);
		else if (str[i] == '$')
			ret = write_dollar_mark(v, str, &i);
		else if (str[i] == '#' && i == 0)
			ret = write_comment_mark(str, &i);
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
	size_t i;
	int newline_opt;
	int ret;

	// int z = 0; //debug
	// while (params[z]) //debug
	// {
	// 	printf("params[%d] = [%s]\n", z, params[z]);
	// 	z++;
	// }
	newline_opt = check_newline_option(params[0]);
	i = newline_opt;
	while (params[i])
	{
		ret = print_strings(v, params[i]);
		if (ret == 1)
			write(1, " ", 1); //dit gaat nog niet goed
		else if (ret < 0)
			return (0);
		i++;
	}
	if (newline_opt == 0 && write(1, "\n", 1) != 1)
		return (1);
	if (!sethistory(&v->history_head, v->line, "1"))
		return (0);
	(void)(params);
	(void)(cmd);
	return (1);
}
