/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:12:57 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/15 13:14:30 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../includes/minishell_merg.h"

int __is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int __is_herdoc(char *s)
{
	if (cmp(s, ">>")|| cmp(s, "<<") || cmp(s, ">") || cmp(s, "<"))
		return (1);
	return (0);
}

static int	check_end_of_command(int i, int j)
{
	if (i >= j)
	{
		__error('\n', 1);
		return (1);
	}
	return (0);
}

int	redir_error(char *command)
{
	bool in_quotes = false;
	bool in_single_quotes = false;
	int	i;
	int	j;

	i = -1;
	j = parse_strlen(command);
    while (++i < j)
    {
		if (!in_quotes && command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && command[i] == '\"')
			in_quotes = !in_quotes;
        if (__is_redir(command[i]) && !in_quotes && !in_single_quotes)
        {
			i++;
			if (check_end_of_command(i, j))
					return (1);
			if (command[i] && command[i] == '>' && command[i] != command[i - 1])
			{
                __error(command[i], 1);
				return (1);
			}
			if (command[i] && command[i] == command[i - 1])
			{
				i++;
				if (check_end_of_command(i, j))
					return (1);
				if (__is_redir(command[i]))
				{
					i++;
					if (command[i] && command[i] == command[i - 1])
						__error(command[i] , 2);
					else
                		__error(command[i - 1], 1);
					return (1);
				}
			}
            if (command[i] == ' ')
			{
				while (command[i] == ' ')
					i++;
				if (check_end_of_command(i, j))
					return (1);
				if (__is_redir(command[i]))
				{
                	__error(command[i], 1);
					return (1);
				}
			}
        }
    }
	return (0);
}

int	pipe_error(char *command, int j)
{
	int	i;

	i = 0;
	while (command && command[i] == ' ')
		i++;
	if (command && command[i] == '|')
	{
		__error('|', 1);
		return (1);
	}
	else
	{
		while (i < j)
		{
			if (command[i] == '|')
			{
				i++;
				while (command[i] == ' ')
					i++;
				if (command[i] == '|' || i >= j)
				{
					__error('|', 1);
					return (1);
				}
			}
			i++;
		}
	}
	return (0);
}

int	qoutes_error(char *command)
{
	bool in_quotes = false;
	bool in_single_quotes = false;
	int	i;
	int	j;

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
	{
		__error('\'', 1);
		return (1);
	}
	if (in_quotes)
	{
		__error('\"', 1);
		return (1);
	}
	return (0);
}

int	syntax_error(char *command)
{
	if (qoutes_error(command))
		return (1);
	if (redir_error(command))
		return (1);
	return (0);
}