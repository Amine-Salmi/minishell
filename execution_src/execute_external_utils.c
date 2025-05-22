/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:49:21 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/14 23:10:08 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_fork_error(int *fd, int pipeline, t_env **env)
{
	perror("fork");
	while (wait(NULL) > 0)
		;
	(*env)->exit_status = 1;
	if (pipeline != -1)
		close(pipeline);
	close(fd[0]);
	close(fd[1]);
	return ;
}

void	wait_last_child(t_env **env, pid_t last_pid)
{
	int	status;

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
