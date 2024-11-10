/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:51:37 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/10 18:19:25 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*__creat_list(t_content *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->content = malloc(sizeof(t_content));
	node->content->value = ft_strdup(content->value);
	node->content->var = ft_strdup(content->var);
	node->exit_status = 0;
	node->next = NULL;
	free(content->var);
	free(content);
	content->var = NULL;
	content = NULL;
	return (node);
}

static void	__add_list_back(t_env **lst, t_content *content)
{
	t_env	*last;
	t_env	*new;

	new = __creat_list(content);
	if (new && lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			last = *lst;
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
}

static int	__special_case(t_content *content, t_env *re)
{
	char		pwd[PATH_MAX];

	content = (t_content *)malloc(sizeof(t_content));
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd");
		free(content);
		return (1);
	}
	content->var = ft_strdup("PWD");
	content->value = ft_strdup(pwd);
	__add_list_back(&re, content);
	content = (t_content *)malloc(sizeof(t_content));
	content->var = ft_strdup("SHLVL");
	content->value = ft_strdup("1");
	__add_list_back(&re, content);
	content = (t_content *)malloc(sizeof(t_content));
	content->var = ft_strdup("_");
	content->value = ft_strdup("/usr/bin/env");
	__add_list_back(&re, content);
	return (0);
}

t_env	*get_env(char **env)
{
	t_content	*content;
	t_env		*re;
	int			i;

	re = NULL;
	i = -1;
	if (!*env)
	{
		if (__special_case(content, re))
			return (NULL);
	}
	else
	{
		i = 0;
		while (env[i])
		{
			content = malloc(sizeof(t_content));
			content->var = __strchr(env[i], '=');
			content->value = getenv(content->var);
			__add_list_back(&re, content);
			i++;
		}
	}
	return (re);
}
