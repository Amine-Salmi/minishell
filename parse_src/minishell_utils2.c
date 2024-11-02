/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:04:33 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/01 16:04:29 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_token	*creat_list(char *command, char **arg, t_opr *file, int number_of_file )
// {
// 	t_token	*node;

// 	node = malloc(sizeof(t_token));
// 	if (!node)
// 		return (NULL);
// 	if (command)
// 		node->command = parse_strdup(command);
// 	node->number_of_file = number_of_file ;
// 	node->arg = arg;
// 	if (file)
// 	{
// 		node->file = malloc(sizeof(t_opr));
// 		if (node->file)
// 			node->file = file;
// 		else
// 		{
// 			free(node->command);
// 			free(node);
// 			return (NULL);
// 		}
// 	}
// 	else
// 		node->file = NULL;
// 	node->next = NULL;
// 	node->prev = NULL;
// 	return (node);
// }

// void	add_list_back(t_token **token, int number_of_file)
// {
// 	t_token	*tmp;
// 	t_token	*new;

// 	new = creat_list((*token)->command, (*token)->arg, (*token)->file, number_of_file );
// 	if (new && token)
// 	{
// 		if (*token == NULL)
// 			*token = new;
// 		else
// 		{
// 			tmp = *token;
// 			while (tmp->next )
// 				tmp = tmp->next;
// 			tmp->next = new;
// 			new->prev = tmp;
// 		}
// 	}
// }

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

t_lst	*__ft_lstnew(t_token *content)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	if (!node)
		return (NULL);
	if (node)
	{
		node->token = content;
		node->next = NULL;
	}
	return (node);
}

void	__ft_lstadd_back(t_lst **lst, t_token *content)
{
	t_lst	*last;
	t_lst	*new;

	new = __ft_lstnew(content);
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
