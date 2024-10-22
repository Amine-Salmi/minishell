/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:51 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/21 21:39:31 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t count_node(t_env *env)
{
    t_env *tmp;
    size_t count;

    tmp = env;
    count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}
// free memory in this function ----------------
char **copy_env(t_env *env)
{
    char **env_copy;
    size_t size;
    int i;
    int j;

    size = count_node(env);
    env_copy = malloc(sizeof(char *) * (size + 1));
    if (!env_copy)
        return (NULL);
    i = 0;
    j = 0;
    while (env)
    {
        env_copy[i] = ft_strdup(env->content->var);
        env_copy[i] = ft_strjoin(env_copy[i], "=");
        env_copy[i] = ft_strjoin(env_copy[i], env->content->value);
        if (!env_copy[i])
            return (NULL);
        env = env->next;
        i++;
    }
    env_copy[i] = NULL;
    return (env_copy);
}

// free memory in this function ----------------

char     *find_var_env(t_env *env, char *var)
{
    char *var_value;

    while (env)
    {
        if (!ft_strcmp(env->content->var, var))
        {
            var_value = ft_substr(env->content->value, 0, ft_strlen(env->content->value));
            return (var_value);
        }
        env = env->next;
    }
    return (NULL);
}
