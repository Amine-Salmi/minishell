/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:12:57 by bbadda            #+#    #+#             */
/*   Updated: 2024/09/13 00:55:02 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error(t_token *token, int j)
{
	int	i;

	i = 0;
    while (i < j)
    {
        if (cmp(token[i].command, ">") || cmp(token[i].command, "<"))
        {
            i++;
			if (i >= j)
				__error('\n', 1);
            while (cmp(token[i].command, " "))
			{
				i++;
				if (i >= j)
				{
                 	__error('\n', 1);
					break ;
				}
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