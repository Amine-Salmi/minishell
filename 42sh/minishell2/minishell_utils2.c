/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:04:33 by bbadda            #+#    #+#             */
/*   Updated: 2024/09/12 23:47:50 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*creat_list(t_token *token)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if(!node)
		return (NULL);
	if (node)
	{
		node->content = token;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	add_list_back(t_list **lst, t_token *token)
{
	t_list	*tmp;
	t_list	*new;

	new = creat_list(token);
	if (new && lst)
	{
		if (*lst == NULL)
		{			
			*lst = __calloc(1, sizeof(t_list));
			*lst = new;
		}
		else
		{
			tmp = *lst;
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
