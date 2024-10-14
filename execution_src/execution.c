/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/14 23:26:22 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int execute_simple_command(t_token *cmd, t_env *env)
{
    pid_t pid;
    int status;
    char *path;
    char *executable_path;

    pid = fork();
    if (pid == 0)
    {
        // if (cmd->file)
        //     redirection_handler(cmd);
        path = find_path(env);
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
