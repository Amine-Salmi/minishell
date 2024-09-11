/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:12:57 by bbadda            #+#    #+#             */
/*   Updated: 2024/09/11 15:00:28 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error(t_token *token, int j)
{
	int	i;

	i = 0;
	printf("j = %d\n", j);
    while (i < j)
    {
		printf("token [%d] = %s\n", i, token[i].command);
        if (token[i].cmd_type == REDIR_IN || token[i].cmd_type == REDIR_OUT)
        {
            i++;
            while (token[i].cmd_type == SPACE)
			{
				if (i >= j)
				{
                 	__error('\n', 1);
					break ;
				}
                i++;
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
	while (i++ < j)
	{
		if (token[i].cmd_type == WORD)
		{
			if (token[i].command[0] == '\'' && token[i].command[ft_strlen(token[i].command) - 1] != '\'')
				__error(' ', 1);
			if (token[i].command[0] == '\"' && token[i].command[ft_strlen(token[i].command) - 1] != '\"')
				__error(' ', 1);
		}
		// if (token[i].cmd_type == SPACE)
		// 	printf("SPACE\n");
		// if (token[i].cmd_type == OPTION)
		// 	printf("OPTION\n");
		// if (token[i].cmd_type == ENV)
		// 	printf("ENV\n");
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