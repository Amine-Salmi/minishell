/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:46 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/08 01:18:50 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_piped_commands(t_lst *cmd, t_env **env)
{
    int fd[2];
    int pipeLine;
	char *executable_path;
	int status;
	t_lst *head;
	head = cmd;
	int last_pid;
	
	pipeLine = -1;
	last_pid = -1;
	int saved_in = -1;
	int saved_out = -1;
	while (cmd)
	{
		if (cmd->next != NULL)
			pipe(fd);
		cmd->token->pid = fork();
		if (cmd->token->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
        	signal(SIGQUIT, SIG_DFL);
			if (pipeLine != -1)
			{
				dup2(pipeLine, STDIN_FILENO);
				close(pipeLine);
			}
			if (cmd->next != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			close(fd[0]);
			close(fd[1]);
			if (cmd->token->file && redirection_handler(cmd->token, *env) == -1)
			{
				exit((*env)->exit_status);
			}
			if (is_builtin(cmd->token->command))
			{
				execute_builtin(cmd->token, env);
				exit((*env)->exit_status);
			}
			if (!cmd->token->command)
				exit((*env)->exit_status);
			executable_path = check_path(cmd->token, *env);
			if (!executable_path)
				exit((*env)->exit_status);
			if (execve(executable_path, cmd->token->arg, copy_env(*env)) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (cmd->token->pid > 0)
		{
			last_pid = cmd->token->pid;
			if (pipeLine != -1)
				close(pipeLine); 
			pipeLine = dup(fd[0]);
			close(fd[0]);
			close(fd[1]);
		}
		cmd = cmd->next;
	}
	cmd = head;
	if (last_pid > 0)
	{
		handler_signal(0);
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			(*env)->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			(*env)->exit_status = 128 + WTERMSIG(status);
		if ((*env)->exit_status == 131)
			ft_putstr_fd("Quit: 3\n", 1);
	}
	while (wait(NULL) > 0)
		;
}
