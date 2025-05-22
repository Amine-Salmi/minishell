/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/17 01:35:03 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	__exec_builtin(t_token *cmd, t_env **env)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = -1;
	saved_stdin = -1;
	if (cmd->file)
	{
		if (save_and_readirect(cmd, env, &saved_stdout, &saved_stdin) == -1)
			return (-1);
	}
	execute_builtin(cmd, env);
	if (saved_stdin != -1 && saved_stdin != -1)
		restore_streams(saved_stdout, saved_stdin);
	return (0);
}

pid_t	__execute_in_child(t_token *cmd, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		while (wait(NULL) > 0)
			;
		(*env)->exit_status = 1;
		return (-1);
	}
	if (pid == 0)
	{
		setup_signals();
		if (cmd->file)
		{
			if (redirection_handler(cmd, *env) == -1)
				exit((*env)->exit_status);
		}
		__check_and_execute(cmd, env);
	}
	return (pid);
}

void	wait_child(pid_t pid, t_env **env)
{
	int	status;

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

int	execute_simple_command(t_token *cmd, t_env **env)
{
	pid_t	pid;

	if (is_builtin(cmd->command) != 0)
	{
		if (__exec_builtin(cmd, env) != 0)
			return (-1);
		return (0);
	}
	handler_signal(0);
	pid = __execute_in_child(cmd, env);
	if (pid == -1)
		return (-1);
	wait_child(pid, env);
	return (0);
}

void	ft_execute(t_lst *cmd, t_env **env)
{
	t_lst	*head;
	char	*heredoc_file;

	head = cmd;
	heredoc_file = ft_strdup("/tmp/heredoc_file");
	while (cmd)
	{
		if (cmd->token->herdoc)
			handle_heredoc(cmd, *env, heredoc_file);
		heredoc_file = rename_file(heredoc_file);
		cmd = cmd->next;
		if (g_signal == true)
		{
			free(heredoc_file);
			g_signal = false;
			return ;
		}
	}
	free(heredoc_file);
	cmd = head;
	if (cmd->next == NULL)
		execute_simple_command(cmd->token, env);
	else if (cmd->next != NULL)
		execute_piped_commands(cmd, env);
}
