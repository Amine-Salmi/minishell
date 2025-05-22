/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:13:36 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/14 19:57:48 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_and_return_executable(t_token *cmd, t_env *env, char **dirs,
		int *flg)
{
	char	*executable_path;
	int		i;

	i = -1;
	while (dirs[++i])
	{
		executable_path = construct_executable_path(dirs[i], cmd->command);
		if (access(executable_path, F_OK) == 0 && cmd->command[0] != '\0')
		{
			if (access(executable_path, X_OK) == 0)
			{
				free_double_p(dirs);
				return (executable_path);
			}
			print_error("Permission denied\n", executable_path);
			free(executable_path);
			env->exit_status = 126;
			*flg = 1;
			break ;
		}
		free(executable_path);
	}
	return (NULL);
}

char	*find_executable_file(t_token *cmd, t_env *env, char *path)
{
	char	*executable_path;
	char	**dirs;
	int		i;
	int		flg;

	i = 0;
	flg = 0;
	dirs = ft_split(path, ':');
	free(path);
	executable_path = check_and_return_executable(cmd, env, dirs, &flg);
	if (executable_path)
		return (executable_path);
	free_double_p(dirs);
	if (!flg)
	{
		print_error("command not found\n", cmd->command);
		env->exit_status = 127;
	}
	return (NULL);
}

char	*get_path_from_cwd(t_token *cmd, t_env *env)
{
	char	cwd_buff[PATH_MAX];
	char	*tmp_path;
	char	*path;

	if (!getcwd(cwd_buff, sizeof(cwd_buff)))
	{
		perror("getcwd");
		return (NULL);
	}
	tmp_path = ft_strjoin(cwd_buff, "/");
	if (!tmp_path)
		return (NULL);
	path = ft_strjoin(tmp_path, cmd->command);
	free(tmp_path);
	if (!path)
		return (NULL);
	if (!file_ok(path, cmd, env))
		return (path);
	free(path);
	return (NULL);
}

char	*check_path(t_token *cmd, t_env *env)
{
	char	*path;

	if (ft_strchr(cmd->command, '/'))
	{
		if (!file_ok(cmd->command, cmd, env))
			return (cmd->command);
		return (NULL);
	}
	path = find_var_env(env, "PATH");
	if (path)
		return (find_executable_file(cmd, env, path));
	else
		return (get_path_from_cwd(cmd, env));
}
