/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:51:37 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/02 20:39:10 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*__creat_list(t_content *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (node)
	{
		node->content = content;
		node->exit_status = 0;
		node->next = NULL;
	}
	return (node);
}

static void	__add_list_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new == NULL || lst == NULL)
		return ;
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

static char	*get_var(char *str, int size)
{
	int		i;
	char	*p;

	i = -1;
	p = malloc(size + 1);
	while (++i < size)
		p[i] = str[i];
	p[i] = '\0';
	return (p);
}

static char	*__strchr(char *str, int c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i++])
	{
		size = i;
		if (str[i] == (char)c)
			return (get_var(str, size));
	}
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
		content = (t_content *)malloc(sizeof(t_content));
		content->var = ft_strdup("TEST");
		content->value = ft_strdup("PATH/TEST");
		__add_list_back(&re, __creat_list(content));
		return (re);
	}
	else
	{
		while (env[++i])
		{
			content = (t_content *)malloc(sizeof(t_content));
			content->var = __strchr(env[i], '=');
			content->value = getenv(content->var);
			__add_list_back(&re, __creat_list(content));
		}
	}
	return (re);
}
