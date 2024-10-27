/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/27 05:56:04 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int execute_simple_command(t_token *cmd, t_env **env)
{
    pid_t pid;
    int status;
    char *executable_path;

    if (is_builtin(cmd->command) != 0)
    {
        execute_builtin(cmd, env);
        return 0;
    }
    pid = fork();
    if (pid == 0)
    {
        // if (cmd->file)
        // {
        //     redirection_handler(cmd);
        // }
        executable_path = check_path(cmd, *env);
        if (!executable_path)
            exit(cmd->exit_status);
        printf("mok\n");
        if (execve(executable_path, cmd->arg, copy_env(*env)) == -1)
        {
		    // should free(array in copy_env if execve is faild)
            perror("execve");
            exit(1);
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
           cmd->exit_status = WEXITSTATUS(status);
    }
    return 0;
}

void ft_execute(t_token *cmd, t_env **env)
{
    if (cmd->command && cmd->next == NULL)
    {
        execute_simple_command(cmd, env);  // should free memory in find_executable_file and path
    }
    else if (cmd->next != NULL)
    {
        execute_piped_commands(cmd, env);  // should free memory in find_executable_file and path.
    }
}
