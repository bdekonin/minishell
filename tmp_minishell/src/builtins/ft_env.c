/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lverdoes <lverdoes@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:36:51 by lverdoes      #+#    #+#                 */
/*   Updated: 2020/10/29 15:02:14 by lverdoes      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_vars *v, char **params)
{
    t_list  *tmp;
    t_env   *node;
    size_t  size;

    tmp = v->env;
    size = ft_array_size((const char **)params);
    if (size == 0)
    {
        while (tmp)
        {
            node = tmp->content;
            ft_printf("%s=%s\n", node->name, node->content);
            tmp = tmp->next;
        }
    }
    else
        return (run_command(v, params));
    return (0);
}
