/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:15:11 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/17 01:47:36 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_to_env(t_env **env, t_env *new_node)
{
	t_env	*last;

	if (!env)
		return ;
	if (env && !*env && new_node)
	{
		*env = new_node;
		(*env)->next = NULL;
	}
	else
	{
		last = lstlast(*env);
		last->next = new_node;
	}
}

t_env	*create_new_elemnts(char *args)
{
	t_env	*new_node;
	char	**elemnts;

	elemnts = split_first_eq(args, '=');
	if (!elemnts)
		return (NULL);
	new_node = allocate_new_node();
	if (!new_node)
	{
		free(elemnts[0]);
		if (elemnts[1])
			free(elemnts[1]);
		free(elemnts);
		return (NULL);
	}
	assign_env_content(new_node, elemnts);
	free(elemnts[0]);
	if (elemnts[1])
		free(elemnts[1]);
	free(elemnts);
	return (new_node);
}

void	print_env_var(t_env *env)
{
	while (env)
	{
		if (!env->content)
			return ;
		printf("declare -x %s", env->content->var);
		if (env->content->value)
			printf("=\"%s\"\n", env->content->value);
		else
			printf("\n");
		env = env->next;
	}
}

void	assign_env_content(t_env *new_node, char **elemnt)
{
	new_node->content->var = ft_strdup(elemnt[0]);
	if (elemnt[1])
		new_node->content->value = ft_strdup(elemnt[1]);
	else
		new_node->content->value = NULL;
}

t_env	*lstlast(t_env *last)
{
	while (last && last->next != NULL)
		last = last->next;
	return (last);
}
