/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:46:38 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/11 22:21:12 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_token *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!ft_strcmp(cmd->arg[i], "-n"))
	{
		i++;
		newline = 0;
	}
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], 1);
		if (cmd->arg[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	ft_cd(t_token *cmd, t_env *env)
{
	char	*path;
	char	oldpath[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(oldpath, sizeof(oldpath)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	path = get_cd_path(cmd, env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		if (!cmd->arg[1])
			free(path);
		return (1);
	}
	update_pwd(env, oldpath);
	if (!cmd->arg[1])
		free(path);
	return (0);
}

int	ft_pwd(t_token *cmd)
{
	char	pwd_path[PATH_MAX];

	if (getcwd(pwd_path, sizeof(pwd_path)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	else
		printf("%s\n", pwd_path);
	return (0);
}

int	ft_env(t_token *cmd, t_env *env)
{
	if (!env)
		return (1);
	if (cmd->arg[1])
		return (1);
	while (env)
	{
		if (env->content->value)
		{
			printf("%s=", env->content->var);
			printf("%s\n", env->content->value);
		}
		env = env->next;
	}
	return (0);
}

int	ft_exit(t_token *cmd, t_env *env)
{
	if (cmd->arg[0])
	{
		if (!cmd->arg[1])
			exit_with_status(cmd, env);
		if (cmd->arg[1])
		{
			check_numeric_arg(cmd, env);
			if (cmd->arg[1] && cmd->arg[2])
			{
				ft_putstr_fd("exit\n", 1);
				print_error("too many arguments\n", cmd->command);
				return (1);
			}
			exit_with_status(cmd, env);
		}
	}
	return (0);
}
