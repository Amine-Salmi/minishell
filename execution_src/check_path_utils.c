/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:51:21 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/14 19:58:03 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_directory(t_token *cmd, char *exec_path, t_env *env)
{
	struct stat	stat_buf;

	if (stat(exec_path, &stat_buf) == -1)
	{
		perror("stat:");
		return (-1);
	}
	if (S_IFDIR == (S_IFMT & stat_buf.st_mode))
	{
		print_error("is a directory\n", cmd->command);
		env->exit_status = 126;
		return (-1);
	}
	return (0);
}

int	file_ok(char *exec_path, t_token *cmd, t_env *env)
{
	if (access(exec_path, F_OK) == -1)
	{
		print_error("No such file or directory\n", cmd->command);
		env->exit_status = 127;
		return (-1);
	}
	if (check_directory(cmd, exec_path, env) == -1)
		return (-1);
	if (access(exec_path, X_OK) == -1)
	{
		print_error("Permission denied\n", cmd->command);
		env->exit_status = 126;
		return (-1);
	}
	return (0);
}

char	*construct_executable_path(char *dir, char *command)
{
	char	*executable_path;
	char	*tmp_path;

	tmp_path = ft_strjoin(dir, "/");
	executable_path = ft_strjoin(tmp_path, command);
	free(tmp_path);
	return (executable_path);
}
