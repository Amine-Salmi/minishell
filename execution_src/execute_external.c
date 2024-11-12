/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:46 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/11 20:53:17 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_and_execute(t_lst *cmd, t_env **env, int *pipeline, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (*pipeline != -1)
	{
		dup2(*pipeline, STDIN_FILENO);
		close(*pipeline);
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
}

void	execute_command(t_lst *cmd, t_env **env)
{
	char	*executable_path;
	char	**env_copy;

	if (!cmd->token->command)
		exit((*env)->exit_status);
	executable_path = check_path(cmd->token, *env);
	if (!executable_path)
		exit((*env)->exit_status);
	env_copy = copy_env(*env);
	if (execve(executable_path, cmd->token->arg, env_copy) == -1)
	{
		free_double_p(env_copy);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	parent_setup(t_lst *cmd, int *pipeline, int *fd)
{
	pid_t	last_pid;

	last_pid = cmd->token->pid;
	if (*pipeline != -1)
		close(*pipeline);
	*pipeline = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
	return (last_pid);
}

void	__process_command(t_lst *cmd, t_env **env, int *pipeline,
		pid_t *last_pid)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	while (cmd)
	{
		if (cmd->next != NULL)
			pipe(fd);
		cmd->token->pid = fork();
		if (cmd->token->pid < 0)
		{
			handle_fork_error(fd, *pipeline, env);
			return ;
		}
		if (cmd->token->pid == 0)
		{
			setup_and_execute(cmd, env, pipeline, fd);
			execute_command(cmd, env);
		}
		else if (cmd->token->pid > 0)
			*last_pid = parent_setup(cmd, pipeline, fd);
		cmd = cmd->next;
	}
	wait_last_child(env, *last_pid);
}

void	execute_piped_commands(t_lst *cmd, t_env **env)
{
	int		pipeline;
	pid_t	last_pid;
	int		fd[2];

	pipeline = -1;
	last_pid = -1;
	fd[0] = -1;
	fd[1] = -1;
	__process_command(cmd, env, &pipeline, &last_pid);
}
