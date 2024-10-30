/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:04:33 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/30 14:57:37 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*creat_list(char *command, char **arg, t_opr *file, int number_of_file )
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	if (command)
		node->command = parse_strdup(command);
	node->number_of_file = number_of_file ;
	node->arg = arg;
	if (file)
	{
		node->file = malloc(sizeof(t_opr));
		if (node->file)
			node->file = file;
		else
		{
			free(node->command);
			free(node);
			return (NULL);
		}
	}
	else
		node->file = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_list_back(t_token **token, t_con *c ,int number_of_file)
{
	t_token	*tmp;
	t_token	*new;

	new = creat_list(c->command, c->arg, c->file, number_of_file );
	if (new && token)
	{
		if (*token == NULL)
			*token = new;
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
	char	**str;
	int		i;

	i = 0;
	str = parse_split(line, ' ');
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
