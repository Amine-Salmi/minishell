/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:20:12 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/13 23:26:12 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_export_elements(char *var)
{
	int	i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (1);
	i = 1;
	while (var[i])
	{
		if (var[i] == '=')
			return (0);
		if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	elemnt_exist(t_env *var, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!ft_strcmp(var->content->var, env->content->var))
		{
			if (var->content->value && ft_strcmp("_", env->content->var))
			{
				free(env->content->value);
				env->content->value = ft_strdup(var->content->value);
				if (!env->content->value)
					return (1);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

t_env	*allocate_new_node(void)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->content = malloc(sizeof(t_content));
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

int	handle_export_arg(t_token *cmd, t_env **env, char *arg)
{
	t_env	*new_node;

	if (!check_export_elements(arg))
	{
		new_node = create_new_elemnts(arg);
		if (!new_node)
			return (1);
		if (!elemnt_exist(new_node, *env))
			add_to_env(env, new_node);
		else
			free_env_content(new_node);
	}
	else
	{
		print_identifier_error(cmd->command, arg);
		return (1);
	}
	return (0);
}

int	ft_export(t_token *cmd, t_env **env)
{
	int	i;

	if (cmd->arg[1] == NULL)
	{
		print_env_var(*env);
		return (0);
	}
	i = 0;
	while (cmd->arg[++i])
	{
		if (handle_export_arg(cmd, env, cmd->arg[i]) != 0)
			return (1);
	}
	return (0);
}
