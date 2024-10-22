/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:46:38 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/21 13:20:26 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// after export and unset -----> updated env

int ft_echo(t_token *cmd)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    while (cmd->arg[i])
    {
        if (!ft_strcmp(cmd->arg[i], "-n"))
        {
            i++;
            newline = 0;
            if (!cmd->arg[i])
                break;
        }
        ft_putstr_fd(cmd->arg[i], 1);
        i++;
    }
    if (newline)
        printf("\n");
    return (0);
}

int ft_cd(t_token *cmd, t_env *env)
{
    char *path;
    char oldpath[PATH_MAX];
    int i;

    i = 0;
    if (getcwd(oldpath, sizeof(oldpath)) == NULL)
    {
        perror("pwd: ");
        return (1);
    }
    if (!cmd->arg[1])
    {
        path = find_var_env(env, "HOME");
        if (path == NULL)
        {
            printf("minishell-0.1: cd: HOME not set\n");
            return 1;
        }
    }
    else if (cmd->arg[1])
        path = cmd->arg[1];
    if (chdir(path) != 0)
    {
        perror("minishell-0.1: cd");
        return (1);
    }
    // while (env)
    // {
    //     if (!ft_strcmp(env->content->var, "OLDPWD"))
    //     {
    //         env->content->value = oldpath;
    //         return 0;
    //     }
    //     env = env->next;
    // }
    return 0;
}

int ft_pwd(t_token *cmd)
{
    char pwd_path[PATH_MAX];
    
    if (getcwd(pwd_path, sizeof(pwd_path)) == NULL)
    {
        perror("pwd: ");
        return (1);
    }
    else
        printf("%s\n", pwd_path);
    return (0);
}

void ft_env(t_env *env)
{
    while (env)
    {
        if (!env->content)
            return ;
        if (env->content->value)
        {
            printf("%s=", env->content->var);
            printf("%s\n", env->content->value);
        }
        env = env->next;
    }
}
