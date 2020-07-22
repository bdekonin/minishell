/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exportt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/22 14:25:17 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"


/*
** TODO lars
**
**
**
**
**         \#      Replace with a `#' character.  This would be useful when
**                 you need a `#' as the first character in one of the argu-
**                 ments created by splitting apart the given string.
**         \$      Replace with a `$' character.
**         \_      If this is found inside of a double-quoted string, then
**                 replace it with a single blank.  If this is found outside
**                 of a quoted string, then treat this as the separator char-
**                 acter between new arguments in the original string.
**         \"      Replace with a <double quote> character.
**         \'      Replace with a <single quote> character.
**         \\      Replace with a backslash character.
**
*/

static int	find_env_var_name(t_env **head, char *name, char *content)
{
	t_env	*tmp;
	
	tmp = *head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
			free(name);
			free(tmp->content);
			tmp->content = content;
			return (1); //existing name found in env list
		}
		tmp = tmp->next;
	}
	return (0); //new name found in env list
}

static int parse_export(t_vars *v, char *str)
{
	size_t i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i == '\'')
			do_something(v, str, &i);
		else if (str[i == '\"')
			do_something(v, str, &i);
		else if (str[i == '=')
			do_something(v, str, &i);
		else
		
		i++;
	}
}

int 			exportt(t_vars *v, t_cmd *cmd, char **params) //tttttt?
{
	size_t	i;
	int 	ret;
	
	int z = 0; //debug
	while (params[z]) //debug
	{
		printf("params[%d] = [%s]\n", z, params[z]);
		z++;
	}
	i = 0;
	while (params[i])
	{
		ret = parse_export(v, params[i]);
		if (ret < 0)
			return (ret);
		i++;
		// if (!find_env_var_name(&v->env_head, array[i], array[i + 1]))
		// {
		// 	env__ft_lstadd_back(&v->env_head, env__ft_lstnew(array[i], array[i + 1]));
		// 	env__ft_lstmove_back("_", v->env_head);	
		// }
	}
	if (!sethistory(&v->history_head, v->line, "0"))
		return (0);
	(void)(cmd);
	return (1);
}
