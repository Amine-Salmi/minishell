/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:04:29 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/09 19:28:46 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_q(char *s_command)
{
	bool	in_single_quotes;
	bool	in_quotes;
	char	*buffer;
	int		buffer_index;
	int		i;

	in_single_quotes = false;
	in_quotes = false;
	buffer = malloc(parse_strlen(s_command) + 1);
	i = -1;
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
	free(s_command);
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
	return (s);
}

int	get_lenth(char *cmd, int x)
{
	int	lenth;

	lenth = 0;
	while (cmd[x] && (ft_isalnum(cmd[x]) || cmd[x] == '_' || cmd[x] == '?'))
	{
		x++;
		lenth++;
	}
	return (lenth);
}

char	*init_and_alloc(char *cmd, int *i, int *j)
{
	int	x;

	*j = 0;
	x = *i;
	return ((char *)malloc(get_lenth(cmd, x) + 1));
}

int	get_env_size(char *cmd, t_env *e)
{
	t_index		index;
	int			size;
	char		*var_name;

	size = 0;
	index.i = -1;
	while (cmd[++index.i])
	{
		if (cmd[index.i] == '$')
		{
			index.i++;
			if (!cmd[index.i] || cmd [index.i] == ' ')
				return (1);
			var_name = init_and_alloc(cmd, &index.i, &index.j);
			while (cmd[index.i] && (ft_isalnum(cmd[index.i])
					|| cmd[index.i] == '_' || cmd[index.i] == '?'))
				var_name[index.j++] = cmd[index.i++];
			var_name[index.j] = '\0';
			size += parse_strlen(replace_env(e, (var_name)));
			index.i--;
		}
		else
			size++;
	}
	return (size);
}
