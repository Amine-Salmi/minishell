/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 00:05:51 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/21 13:18:57 by asalmi           ###   ########.fr       */
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
    return (0);
}

int execute_builtin(t_token *cmd, t_env **env)
{
    if (!ft_strcmp(cmd->command, "echo"))
        ft_echo(cmd);
    if (!ft_strcmp(cmd->command, "cd"))
        ft_cd(cmd, *env);
    if (!ft_strcmp(cmd->command, "pwd"))
        ft_pwd(cmd);
    if (!ft_strcmp(cmd->command, "env"))
        ft_env(*env);
    if (!ft_strcmp(cmd->command, "export"))
        ft_export(cmd, *env);
    if (!ft_strcmp(cmd->command, "unset"))
        ft_unset(cmd, env);
    return (0);
}
