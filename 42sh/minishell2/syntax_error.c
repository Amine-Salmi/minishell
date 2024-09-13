/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:12:57 by bbadda            #+#    #+#             */
/*   Updated: 2024/09/13 10:51:28 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_end_of_command(int i, int j)
{
	if (i >= j)
	{
		__error('\n', 1);
		return (1);
	}
	return (0);
}

int	redir_error(t_token *token, int j)
{
	int	i;

	i = 0;
    while (i < j)
    {
        if (cmp(token[i].command, ">") || cmp(token[i].command, "<") 
			|| cmp(token[i].command, ">>") || cmp(token[i].command, "<<"))
        {
            i++;
			if (check_end_of_command(i, j))
				break ;
			if (!cmp(token[i].command, token[i - 1].command))
			{
				if (cmp(token[i].command, "<"))
                	__error('<', 1);
				else
					__error('\n', 1);	
				break ;
			}
            if (cmp(token[i].command, " "))
			{
				i++;
				if (check_end_of_command(i, j))
					break ;
			}
            if (token[i].cmd_type == REDIR_IN || token[i].cmd_type == REDIR_OUT)
			{
                __error(token[i].cmd_type, 1);
					break ;
			}
        }
        i++;
    }
	return (0);
}

int	pipe_error(t_token *token, int j)
{
	int	i;

	i = 0;
	if (token[0].cmd_type == PIPE)
		__error('|', 1);
	else
	{
		while (i < j)
		{
			if (token[i].cmd_type == PIPE)
			{
				i++;
				while (token[i].cmd_type == SPACE)
					i++;
				if (token[i].cmd_type == PIPE || i >= j)
					__error('|', 1);
			}
			i++;
		}
	}
	return (0);
}

int	qoutes_error(t_token *token, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (cmp(token[i].command, "'"))
		{
			i++;
			i++;
			if (i >= j || !cmp(token[i].command, "'"))
				__error('\'', 1);
		}
		else if (cmp(token[i].command, "\""))
		{
			i++;
			i++;
			if (i >= j || !cmp(token[i].command, "\""))
				__error('"', 1);
		}
		// if (token[i].cmd_type == SPACE)
		// 	printf("SPACE\n");
		// if (token[i].cmd_type == OPTION)
		// 	printf("OPTION\n");
		// if (token[i].cmd_type == ENV)
		// 	printf("ENV\n");
		i++;
	}
	return (0);
}

int	syntax_error(t_token *token, int j)
{
	qoutes_error(token, j);
	pipe_error(token, j);
	redir_error(token, j);
	return (0);
}