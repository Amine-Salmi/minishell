/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:40:06 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/12 00:07:09 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cd_path(t_token *cmd, t_env *env)
{
	char	*path;

	path = NULL;
	if (!cmd->arg[1])
	{
		path = find_var_env(env, "HOME");
		if (path == NULL)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else
		path = cmd->arg[1];
	return (path);
}

int	exit_with_status(t_token *cmd, t_env *env)
{
	ft_putstr_fd("exit\n", 1);
	if (cmd->arg[1])
		exit(ft_atoi(cmd->arg[1]));
	else
		exit(env->exit_status);
}

void	check_numeric_arg(t_token *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd->arg[1][i])
	{
		if (ft_isalpha(cmd->arg[1][i]))
		{
			ft_putstr_fd("exit\n", 1);
			print_error("numeric argument required\n", cmd->arg[1]);
			env->exit_status = 255;
			exit(env->exit_status);
		}
		i++;
	}
}

void	print_identifier_error(char *command, char *identifier)
{
	if (!ft_strcmp(command, "unset"))
		printf("mminishell: unset: `%s':not a valid identifier\n", identifier);
	else if (!ft_strcmp(command, "export"))
		printf("mminishell: export: `%s':not a valid identifier\n", identifier);
}
