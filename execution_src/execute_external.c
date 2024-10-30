/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:46 by asalmi            #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/10/25 16:13:57 by bbadda           ###   ########.fr       */
=======
/*   Updated: 2024/10/27 06:27:19 by asalmi           ###   ########.fr       */
>>>>>>> daec7412266d908346f2912244ea5c3a4c79933a
=======
/*   Updated: 2024/10/29 19:12:35 by asalmi           ###   ########.fr       */
>>>>>>> e5ddf848b525aaadbafc2d758a4a0ac87bad6fcc
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_piped_commands(t_token *cmd, t_env **env)
{
    int fd[2];
    int pipeLine;
	char *path;
	char *executable_path;
	int status;
	t_env *my_env;
	t_token *head;

	head = cmd;
	pipeLine = -1;

    while (cmd)
    {
		if (cmd->next != NULL)
			pipe(fd);
		handler_signal(0);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
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
			// if (cmd->redirection)
			// 	redirection_handler(cmd);
			if (is_builtin(cmd->command))
			{
				execute_builtin(cmd, env);
				exit(EXIT_SUCCESS);
			}
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
		else if (cmd->pid > 0)
		{
			if (pipeLine != -1)
				close(pipeLine);
			pipeLine = dup(fd[0]);
			close(fd[0]);
			close(fd[1]);
		}
        cmd = cmd->next;
    }
	cmd = head;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			handler_signal(1);
			if (WIFEXITED(status))
				(*env)->exit_status = WEXITSTATUS(status);
		}
		cmd = cmd->next;
	}
	
}

