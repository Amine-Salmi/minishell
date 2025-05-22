/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_special_case.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:09:10 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/16 01:09:54 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*__creat_list_special_case(t_content *content)
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
	free(content->value);
	free(content);
	content = NULL;
	return (node);
}

void	__add_list_special_case(t_env **lst, t_content *content)
{
	t_env	*last;
	t_env	*new;

	new = __creat_list_special_case(content);
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

char	*__env_heredoc(char *cmd, t_env *e)
{
	t_buffer	string;
	int			buffer_index;
	int			i;
	bool		in_single_quotes;
	bool		in_quotes;

	in_single_quotes = false;
	in_quotes = false;
	i = 0;
	buffer_index = 0;
	string.cmd = parse_strdup(cmd);
	string.buffer = __calloc(get_env_size(cmd, e) + 10, 1);
	while (cmd[i])
	{
		quotes_status(cmd, &i, &in_single_quotes, &in_quotes);
		if (cmd[i + 1] && cmd[i] == '$' && cmd[i + 1] != ' ' && 
			cmd[i + 1] != '\"')
			handle_dollar_sign(string, &i, e, &buffer_index);
		else
			string.buffer[buffer_index++] = cmd[i++];
		string.buffer[buffer_index] = '\0';
	}
	free(string.cmd);
	return (string.buffer);
}
