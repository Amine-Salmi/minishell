/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/22 01:05:16 by asalmi           ###   ########.fr       */
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
        //     printf("=========== %p ===========\n", cmd->file);
        //     redirection_handler(cmd);
        // }
        // path = find_var_env(*env, "PATH");
        executable_path = check_path(cmd, *env);
        // printf("------------- -------------> %s\n", executable_path);
        if (execve(executable_path, cmd->arg, copy_env(*env)) == -1)
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

void ft_execute(t_token *cmd, t_env **env)
{
    // if (cmd->file->del)
    //     handle_heredoc(cmd);
    if (cmd->arg[0] && cmd->next == NULL)
    {
        if (execute_simple_command(cmd, env) != 0) // should free memory in find_executable_file and path.
            exit(EXIT_FAILURE);
    }
    else if (cmd->next != NULL)
    {
        execute_piped_commands(cmd, env);  // should free memory in find_executable_file and path.
    }
}
