/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:04:29 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/23 17:04:21 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_env(char *cmd)
{
	int i;

	i = 0;
	if (cmd[i] == '$')
	{
		if (cmd[i])
			i++;
		if (cmd[i] == '$')
			return (0);
		if (ft_isdigit(cmd[i]))
			return (2);
		if (cmd[i] == '\'' || cmd[i] == '\"')
			return (3);
		return (1);
	}
	else
		return (-1);
}

char	*replace_env(t_env *e, char *s)
{
	while (e)
	{
		if (cmp(e->content->var, s))
			return (parse_strdup(e->content->value));
		e = e->next;
	}
	return (parse_strdup(""));
}

char	*remove_q(char *s_command)
{
	bool	in_single_quotes;
	bool	in_quotes;
	char	*buffer;
	int		buffer_index;

	in_single_quotes = false;
	in_quotes = false;
	buffer = malloc(parse_strlen(s_command) + 1);
	int i = -1;
	buffer_index = 0;
	while (s_command[++i])
	{
		if (!in_quotes && s_command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && s_command[i] == '\"')
			in_quotes = !in_quotes;
		else
			buffer[buffer_index++] = s_command[i];
	}
	buffer[buffer_index] = '\0';
	return (buffer);
}

char	*add_token(char *buffer, int *buffer_index)
{
	char	*s;

	s = NULL;
	if (*buffer_index > 0)
	{
		buffer[*buffer_index] = '\0';
		s = parse_strdup(buffer);
		*buffer_index = 0;
	}
	return(s);
}

int	get_env_size(char *cmd, t_env *e)
{
	int		i;
	int		j;
	int		size;
	char	var_name[256];

	size = 0;
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			i++;
			j = 0;
			while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
				var_name[j++] = cmd[i++];
			size += parse_strlen(replace_env(e, var_name));
		}
		i++;
		size++;
	}
	return (size);
}
