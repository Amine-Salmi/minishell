/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:04:33 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/09 11:13:58 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*creat_list(char *command, char **arg)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if(!node)
		return (NULL);
	if (node)
	{
		node->command = command;
		node->arg = arg;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	add_list_back(t_token **token, t_con *c)
{
	t_token	*tmp;
	t_token	*new;

	new = creat_list(c->command, c->arg);
	if (new && token)
	{
		if (*token == NULL)
		{			
			*token = __calloc(1, sizeof(t_token));
			*token = new;
		}
		else
		{
			tmp = *token;
			while (tmp->next )
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
		}
	}
}

char	*get_pipe(char *line)
{
	int i = 0;
	char	**str;
	str = ft_split(line, ' ');
	while (str[i])
	{
		if (cmp(str[i], "|") && !str[i + 1])
			return (str[i]);
		i++;
	}
	return (NULL);
}
int	is_cmd(char *str)
{
	if (!cmp(str, "|") && cmp(str, ">") && cmp(str, "<") && 
		cmp(str, "'") && cmp(str, " "))
		return (0);
	return (1);
}

// void	tokenize(t_token is, char *str)
// {
// 		is.command[0] = str;
// 		if (is_cmd(str) == 1)
// 			is.cmd_type = 1;
// 		else
// 			is.cmd_type = 2;
	// else
	// 	printf("(null)\n");
// }
