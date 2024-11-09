/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:51:37 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/09 13:44:57 by bbadda           ###   ########.fr       */
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
	return (NULL);
}

t_env	*get_env(char **env)
{
	t_content	*content;
	t_env		*re;
	int			i;
	char		pwd[PATH_MAX];

	re = NULL;
	i = -1;
	if (!*env)
	{
		printf("if\n");
		content = (t_content *)malloc(sizeof(t_content));
		if(getcwd(pwd, sizeof(pwd)) == NULL)
		{
			perror("getcwd");
			free(content);
			return NULL;
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
	}
	else
	{
		printf("else\n");
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
