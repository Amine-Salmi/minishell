/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:04:50 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/11 08:04:51 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	restore_streams(int saved_out, int saved_in)
{
	dup2(saved_out, STDOUT_FILENO);
	dup2(saved_in, STDIN_FILENO);
	close(saved_out);
	close(saved_in);
}

int	save_and_readirect(t_token *cmd, t_env **env, int *saved_out, int *saved_in)
{
	*saved_out = dup(STDOUT_FILENO);
	*saved_in = dup(STDIN_FILENO);
	if (redirection_handler(cmd, *env) == -1)
	{
		(*env)->exit_status = 1;
		restore_streams(*saved_out, *saved_in);
		return (-1);
	}
	return (0);
}

void	__check_and_execute(t_token *cmd, t_env **env)
{
	char	*executable_path;
	char	**env_copy;

	if (!cmd->command)
		exit((*env)->exit_status);
	executable_path = check_path(cmd, *env);
	if (!executable_path)
		exit((*env)->exit_status);
	env_copy = copy_env(*env);
	if (execve(executable_path, cmd->arg, env_copy) == -1)
	{
		perror("execve");
		free_double_p(env_copy);
		exit(EXIT_FAILURE);
	}
}
