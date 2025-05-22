/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:59:14 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/12 01:44:28 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	__is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	__is_herdoc(char *s)
{
	if (cmp(s, ">>") || cmp(s, "<<") || cmp(s, ">") || cmp(s, "<"))
		return (1);
	return (0);
}

int	check_end_of_command(int i, int j)
{
	if (i >= j)
	{
		__error('\n', 1);
		return (1);
	}
	return (0);
}

int	redir_error_check(char *command, int *i, int *j)
{
	(*i)++;
	if (check_end_of_command(*i, *j))
		return (1);
	if (__is_redir(command[*i]))
	{
		(*i)++;
		if (command[*i] && command[*i] == command[(*i) - 1])
		{
			__error(command[*i], 2);
		}
		else
			__error(command[(*i) - 1], 1);
		return (1);
	}
	return (0);
}

int	check_all_thing(char *command, int *i, int *j)
{
	(*i)++;
	if (check_end_of_command(*i, *j))
	{
		return (1);
	}
	if (command[*i] && command[*i] == '>' && command[*i] != command[*i - 1])
		return (__error(command[*i], 1), 1);
	if (command[*i] && command[*i] == command[(*i) - 1])
	{
		if (redir_error_check(command, i, j))
			return (1);
	}
	if (command[*i] == ' ')
	{
		while (command[*i] == ' ')
			(*i)++;
		if (check_end_of_command(*i, *j))
			return (1);
		if (__is_redir(command[*i]))
			return (__error(command[*i], 1), 1);
	}
	return (0);
}
