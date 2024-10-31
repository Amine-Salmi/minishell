/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:43:30 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/31 00:12:50 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_unset_elements(char *var)
{
    int i;

    if (!ft_isalpha(var[0]) && var[0] != '_')
        return (1);
    i = 1;
    while (var[i])
    {
        if (var[i] == '=')
            return (0);
        if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
            return (1);
        i++;
    }
    return (0);
}

void remove_elemnts(t_env **env, char *d_var)
{
    t_env *tmp;
    t_env *prev;
    
    if (!env || !*env)
        return ;
    tmp = *env;
    prev = NULL;
    if (tmp && !ft_strcmp(tmp->content->var, d_var))
    {
        (*env) = tmp->next;
        free(tmp);
        return ;
    }
    while (tmp)
    {
        if (!ft_strcmp(tmp->content->var, d_var))
        {
            if (prev)
                prev->next = tmp->next;
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    } 
}

int ft_unset(t_token *cmd, t_env **env)
{
    int i;

    if (!cmd->arg[1])
        return (0);
    i = 1;
    while (cmd->arg[i])
    {
        if (!check_unset_elements(cmd->arg[i]))
        {
            if (find_var_env(*env, cmd->arg[i]))
                remove_elemnts(env, cmd->arg[i]);
        }
        else
        {
            printf("mminishell-0.1: export: `%s': a not valid identifier\n", cmd->arg[i]);
            return (1);
        }
        i++;
    }
    return (0);
}
