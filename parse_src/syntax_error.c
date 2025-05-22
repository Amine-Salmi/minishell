/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:12:57 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/17 01:28:50 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_error(char *command)
{
	bool	in_quotes;
	bool	in_single_quotes;
	int		i;
	int		j;

	in_quotes = false;
	in_single_quotes = false;
	j = parse_strlen(command);
	i = -1;
	while (++i < j)
	{
		if (!in_quotes && command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && command[i] == '\"')
			in_quotes = !in_quotes;
		if (__is_redir(command[i]) && !in_quotes && !in_single_quotes)
		{
			if (check_all_thing(command, &i, &j))
				return (1);
		}
	}
	return (0);
}

static void	__init_data(bool *in_q, bool *in_sq, int *i)
{
	*in_q = false;
	*in_sq = false;
	*i = 0;
}

int	pipe_error(char *command, int j)
{
	bool	in_q;
	bool	in_sq;
	int		i;

	__init_data(&in_q, &in_sq, &i);
	while (command[i] && command[i] == ' ')
		i++;
	if (command[i] && command[i] == '|')
		return (__error('|', 1), 1);
	else
	{
		while (i++ < j)
		{
			quotes_status(command, &i, &in_sq, &in_q);
			if (command[i] == '|')
			{
				i++;
				while (command[i] && command[i] == ' ')
					i++;
				if ((command[i] == '|' || i >= j) && !in_sq && !in_q)
					return (__error('|', 1), 1);
			}
		}
	}
	return (0);
}

int	qoutes_error(char *command)
{
	bool	in_quotes;
	bool	in_single_quotes;
	int		i;
	int		j;

	in_single_quotes = false;
	in_quotes = false;
	j = parse_strlen(command);
	i = -1;
	while (++i < j)
	{
		if (!in_quotes && command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && command[i] == '\"')
			in_quotes = !in_quotes;
	}
	if (in_single_quotes)
		return (__error('\'', 1), 1);
	if (in_quotes)
		return (__error('\"', 1), 1);
	return (0);
}

int	syntax_error(char *command, t_env *env)
{
	if (qoutes_error(command))
	{
		env->exit_status = 258;
		return (1);
	}
	if (redir_error(command))
	{
		env->exit_status = 258;
		return (1);
	}
	return (0);
}
