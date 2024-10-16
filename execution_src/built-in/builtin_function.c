/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:46:38 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/16 00:43:29 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(t_token *cmd)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    while (cmd->arg[i])
    {
        if (!ft_strncmp(cmd->arg[i], "-n", ft_strlen(cmd->arg[i])))
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
    int i;

    i = 0;
    if (!cmd->arg[1])
    {
        path = find_var_env(env, "HOME");
        if (path == NULL)
        {
            printf("-  minishell-0.1: cd: HOME not set\n");
            return 1;
        }
    }
    else if (cmd->arg[1])
        path = cmd->arg[1];
    if (chdir(path) != 0)
    {
        perror("cd");
        exit(EXIT_FAILURE);
    }
    return 0;
}