/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/29 19:12:45 by asalmi           ###   ########.fr       */
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
    handler_signal(0);
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        // if (cmd->file)
        // {
        //     redirection_handler(cmd);
        // }
        executable_path = check_path(cmd, *env);
        if (!executable_path)
            exit((*env)->exit_status);
        if (execve(executable_path, cmd->arg, copy_env(*env)) == -1)
        {
		    // should free(array in copy_env if execve is faild)
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        handler_signal(1);
        if (WIFEXITED(status))
           (*env)->exit_status = WEXITSTATUS(status);
        if (WIFSIGNALED(status))
        {
           (*env)->exit_status = 128 + WTERMSIG(status);
           if ((*env)->exit_status == 131)
                printf("Quit: 3\n");
        }
    }
    return 0;
}

void ft_execute(t_token *cmd, t_env **env)
{
    if (cmd->command && cmd->next == NULL)
    {
        execute_simple_command(cmd, env);  // should free memory in find_executable_file and path.
    }
    else if (cmd->next != NULL)
    {
        execute_piped_commands(cmd, env);  // should free memory in find_executable_file and path.
    }
}
