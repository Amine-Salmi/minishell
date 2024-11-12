/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:43:30 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/12 00:08:38 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_unset_elements(char *var)
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

void	free_env_content(t_env *node)
{
	if (!node)
		return ;
	free(node->content->var);
	if (node->content->value)
		free(node->content->value);
	free(node->content);
	free(node);
}

int	remove_head_node(t_env **head, char *d_var)
{
	t_env	*tmp;

	if (!head || !*head)
		return (0);
	tmp = *head;
	if (tmp && !ft_strcmp(tmp->content->var, d_var))
	{
		if (tmp->next != NULL)
			*head = tmp->next;
		free_env_content(tmp);
		return (1);
	}
	return (0);
}

void	remove_elemnts(t_env **env, char *d_var)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || !*env)
		return ;
	tmp = *env;
	if (remove_head_node(env, d_var))
		return ;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->content->var, d_var))
		{
			if (prev)
				prev->next = tmp->next;
			free_env_content(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_token *cmd, t_env **env)
{
	int		i;
	char	*remove_var;

	remove_var = NULL;
	if (!cmd->arg[1])
		return (0);
	i = 0;
	while (cmd->arg[++i])
	{
		if (!ft_strcmp(cmd->arg[i], "_"))
			return (0);
		if (!check_unset_elements(cmd->arg[i]))
		{
			remove_var = find_var_env(*env, cmd->arg[i]);
			if (remove_var)
				remove_elemnts(env, cmd->arg[i]);
			free(remove_var);
		}
		else
		{
			print_identifier_error(cmd->command, cmd->arg[i]);
			return (1);
		}
	}
	return (0);
}
