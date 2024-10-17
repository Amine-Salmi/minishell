/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/16 21:14:03 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_builtin(const char *cmd)
{
    if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
        return (1);
    if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
        return (1);
    if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
        return (1);
    if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
        return (1);
    if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
        return (1);
    return (0);
}

int execute_simple_command(t_token *cmd, t_env *env)
{
    pid_t pid;
    int status;
    char *path;
    char *executable_path;

    if (is_builtin(cmd->command) != 0)
    {
        if (ft_export(cmd, env) != 0)
            exit(EXIT_FAILURE);
        return 0;
    }
    pid = fork();
    if (pid == 0)
    {
        // if (cmd->file)
        //     redirection_handler(cmd);
        path = find_var_env(env, "PATH");
        executable_path = find_executable_file(cmd->command, path);
        if (execve(executable_path, cmd->arg, copy_env(env)) == -1)
        {
			// should free(array in copy_env if execve is faild)
            perror("execve");
            return 1;
        }
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
    return 0;
}

void ft_execute(t_token *cmd, t_env *env)
{
    if (cmd->next == NULL)
    {
        if (execute_simple_command(cmd, env) != 0) // should free memory in find_executable_file and path.
            exit(EXIT_FAILURE);
    }
    else if (cmd->next != NULL)
    {
        execute_piped_commands(cmd, env); // // should free memory in find_executable_file and path.
    }
}
