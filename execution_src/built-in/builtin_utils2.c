/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 00:05:51 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/01 19:57:26 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin(const char *cmd)
{
    if (!ft_strcmp(cmd, "echo"))
        return (1);
    if (!ft_strcmp(cmd, "cd"))
        return (1);
    if (!ft_strcmp(cmd, "pwd"))
        return (1);
    if (!ft_strcmp(cmd, "env"))
        return (1);
    if (!ft_strcmp(cmd, "export"))
        return (1);
    if (!ft_strcmp(cmd, "unset"))
        return (1);
    // printf("---------> %s\n", cmd);
    return (0);
}

void execute_builtin(t_token *cmd, t_env **env)
{
    int res;

    if (!ft_strcmp(cmd->command, "echo"))
        res = ft_echo(cmd);
    if (!ft_strcmp(cmd->command, "cd"))
        res = ft_cd(cmd, *env);
    if (!ft_strcmp(cmd->command, "pwd"))
        res = ft_pwd(cmd);
    if (!ft_strcmp(cmd->command, "env"))
        res = ft_env(cmd, *env);
    if (!ft_strcmp(cmd->command, "export"))
        res = ft_export(cmd, env);
    if (!ft_strcmp(cmd->command, "unset"))
        res = ft_unset(cmd, env);
    if (res == 0)
        (*env)->exit_status = 0;
    else
        (*env)->exit_status = 1;
}

// should free memmory in this function 
int    update_pwd(t_env *env, char *old_pwd)
{
    char pwd[PATH_MAX];
    t_env *new;
    t_env *head;
    int flg;

    flg = 0;
    head = env;
    if(getcwd(pwd, sizeof(pwd)) == NULL)
    {
        perror("getcwd:");
        free(new);
        free(new->content);
        return 1;
    } 
    while (env)
    {
        if (!ft_strcmp(env->content->var, "PWD"))
            env->content->value = ft_strdup(pwd);
        if (!ft_strcmp(env->content->var, "OLDPWD"))
        {
            env->content->value = ft_strdup(old_pwd);
            flg = 1;
        }
        env = env->next;
    }
    if (flg == 0)
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return (1);
        new->content = malloc(sizeof(t_content));
        if (!new->content)
        {
            free(new);
            return (1);
        }
        new->content->var = ft_strdup("OLDPWD");
        new->content->value = ft_strdup(old_pwd);
        new->next = NULL;
        add_to_env(&head, new);
    }
    return 0;
}
