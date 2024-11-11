/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:43:30 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/11 04:04:32 by asalmi           ###   ########.fr       */
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

    if (tmp && !ft_strcmp(tmp->content->var, d_var))
    {
        if (tmp->next != NULL)
            *env = tmp->next;
	 	free(tmp->content->var);
        if (tmp->content->value)
	 	    free(tmp->content->value);
        free(tmp->content);
        free(tmp);
        return ;
    }
    prev = NULL;
    while (tmp)
    {
        if (!ft_strcmp(tmp->content->var, d_var))
        {
            if (prev)
                prev->next = tmp->next;
            free(tmp->content->var);
            if (tmp->content->value)
	 	        free(tmp->content->value);
            free(tmp->content);
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
    char *remove_var;

    remove_var = NULL;
    if (!cmd->arg[1])
        return (0);
    i = 1;
    while (cmd->arg[i])
    {
        if (!ft_strcmp(cmd->arg[i], "_"))
            return 0;
        if (!check_unset_elements(cmd->arg[i]))
        {
            remove_var = find_var_env(*env, cmd->arg[i]);
            if (remove_var)
                remove_elemnts(env, cmd->arg[i]);
            free(remove_var);
        }
        else
        {
            printf("mminishell-0.1: unset: `%s': a not valid identifier\n", cmd->arg[i]);
            return (1);
        }
        i++;
    }
    return (0);
}
