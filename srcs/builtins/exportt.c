/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exportt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bdekonin <bdekonin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:14:06 by bdekonin      #+#    #+#                 */
/*   Updated: 2020/07/18 12:45:17 by lverdoes      ########   odam.nl         */
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

static int	trim_strings(char **src, size_t size)
{
	char	set[3];
	size_t	i;
	char	*tmp;

	set[0] = 34;
	set[1] = 39;
	set[2] = 0;
	i = 1;
	while (src[i])
	{	
		tmp = ft_strtrim(src[i], set);
		if (!tmp)
		{
			ft_free_array((void**)src, size);
			return (0); //malloc
		}
		free(src[i]);
		src[i] = tmp;
		i++;
	}
	return (1);
}

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

int 			exportt(t_vars *v, t_cmd *cmd, char **params) //tttttt?
{
	if (!params) //del this
		return (0); //del this
	printf("cmd = [%s]\n", cmd->line);
	char	**array;
	size_t	size;
	size_t	i;
	
	size = 0;
	array = ft_split_sep_exep(cmd->line, " =", &size);
	if (!array || size % 2 == 0) //size should be odd.
		return (0); //malloc	
	if (!trim_strings(array, size))
		return (0); //malloc
	i = 1; //i = 1, because: array[0] == "export"
	while (i < size)
	{
		if (!find_env_var_name(&v->env_head, array[i], array[i + 1]))
		{
			env__ft_lstadd_back(&v->env_head, env__ft_lstnew(array[i], array[i + 1]));
			env__ft_lstmove_back("_", v->env_head);	
		}
		i += 2;
	}
	if (!sethistory(&v->history_head, v->line, "0"))
		return (0);
	(void)(cmd);
	return (1);
}