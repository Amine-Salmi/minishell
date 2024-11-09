/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/09 00:33:33 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int execute_simple_command(t_token *cmd, t_env **env)
{
    pid_t pid;
    int status;
    char *executable_path;
    int saved_stdout;
    int saved_stdin;
    
    saved_stdout = -1;
    saved_stdin = -1;
    if (is_builtin(cmd->command) != 0)
    {
        if (cmd->file)
        {
            saved_stdout = dup(STDOUT_FILENO);
            saved_stdin = dup(STDIN_FILENO);
            if (redirection_handler(cmd, *env) == -1)
                return (-1);
        }
        execute_builtin(cmd, env);
        if (saved_stdin != -1 && saved_stdin != -1)
        {
            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdout);
            close(saved_stdin);
        }
        return (0);
    }
    handler_signal(0);
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (cmd->file)
        {
            if (redirection_handler(cmd, *env) == -1)
                exit((*env)->exit_status);
        }
        if (!cmd->command)
            exit((*env)->exit_status);
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
        if (WIFEXITED(status))
           (*env)->exit_status = WEXITSTATUS(status);
        if (WIFSIGNALED(status))
        {
           (*env)->exit_status = 128 + WTERMSIG(status);
           if ((*env)->exit_status == 131)
                ft_putstr_fd("Quit: 3\n", 1);
        }
    }
    return 0;
}

void ft_execute(t_lst *cmd, t_env **env)
{
    t_lst *head;

    head = cmd;
    while (cmd)
    {
        if (cmd->token->herdoc)
            handle_heredoc(cmd, *env);
        cmd = cmd->next;
    }
    if (g_signal)
    {
        return ;
    }
    cmd = head;
    if (cmd->next == NULL)
    {
        execute_simple_command(cmd->token, env);  // should free memory in find_executable_file and path.
    }
    else if (cmd->next != NULL)
    {
        execute_piped_commands(cmd, env);  // should free memory in find_executable_file and path.
    }
}
