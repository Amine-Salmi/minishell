/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:46:38 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/27 02:05:39 by asalmi           ###   ########.fr       */
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
    if (!ft_strcmp(cmd->arg[1], "-n")) 
    {
        i++;
        newline = 0;
    }
    while (cmd->arg[i])
    {
        ft_putstr_fd(cmd->arg[i], 1);
        if (cmd->arg[i + 1] != NULL)
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", 1);
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
        perror("getcwd:");
        return (1);
    }
    if (!cmd->arg[1])
    {
        path = find_var_env(env, "HOME");
        if (path == NULL)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return 1;
        }
    }
    else if (cmd->arg[1])
        path = cmd->arg[1];
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        return (1);
    }
    update_pwd(env, oldpath);
    return 0;
}

int ft_pwd(t_token *cmd)
{
    char pwd_path[PATH_MAX];

    if (getcwd(pwd_path, sizeof(pwd_path)) == NULL)
    {
        perror("pwd:");
        return (1);
    }
    else
        printf("%s\n", pwd_path);
    return (0);
}

int ft_env(t_token *cmd, t_env *env)
{
    // if (!env)
    //     return 1;
    while (env)
    {
        if (env->content->value)
        {
            printf("%s=", env->content->var);
            printf("%s\n", env->content->value);
        }
        env = env->next;
    }
    return 0;
}
