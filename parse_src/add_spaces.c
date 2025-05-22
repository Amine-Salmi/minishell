/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:26:36 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/12 02:10:04 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	__helper_function(int *i, t_buffer str, int *j, int condition)
{
	if (condition == 1)
	{
		if (*i > 0 && str.cmd[(*i) - 1] != ' ' && (!str.in_sq && !str.in_q))
			str.buffer[(*j)++] = ' ';
		str.buffer[(*j)++] = str.cmd[(*i)++];
		str.buffer[(*j)++] = str.cmd[*i];
		if (str.cmd[(*i) + 1] && str.cmd[(*i) + 1] != ' '
			&& (!str.in_sq && !str.in_q))
			str.buffer[(*j)++] = ' ';
	}
	else
	{
		if (*i > 0 && str.cmd[(*i) - 1] != ' ' && (!str.in_sq && !str.in_q))
			str.buffer[(*j)++] = ' ';
		str.buffer[(*j)++] = str.cmd[*i];
		if (str.cmd[(*i) + 1] && str.cmd[(*i) + 1] != ' ' 
			&& (!str.in_sq && !str.in_q) && !__is_redir(str.cmd[(*i) + 1]))
			str.buffer[(*j)++] = ' ';
	}
}

static int	__check_and_init(char *cmd, bool *in_q, bool *in_sq, int *index)
{
	if (cmd == NULL)
		return (1);
	*in_sq = false;
	*in_q = false;
	*index = 0;
	return (0);
}

char	*add_spaces(char *cmd)
{
	t_index		index;
	t_buffer	str;

	str.cmd = cmd;
	if (__check_and_init(cmd, &str.in_q, &str.in_sq, &index.j))
		return (NULL);
	index.i = -1;
	str.buffer = malloc(parse_strlen(cmd) * 3);
	if (str.buffer == NULL)
		return (NULL);
	while (str.cmd[++index.i])
	{
		if (str.cmd[index.i] == '\'' || str.cmd[index.i] == '\"')
			quotes_status(str.cmd, &index.i, &str.in_sq, &str.in_q);
		if ((str.cmd[index.i] == '>' && str.cmd[index.i + 1] == '>') 
			|| (str.cmd[index.i] == '<' && str.cmd[index.i + 1] == '<'))
			__helper_function(&index.i, str, &index.j, 1);
		else if (str.cmd[index.i] == '>' || str.cmd[index.i] == '<')
			__helper_function(&index.i, str, &index.j, 0);
		else
			str.buffer[index.j++] = str.cmd[index.i];
	}
	str.buffer[index.j] = '\0';
	return (str.buffer);
}
