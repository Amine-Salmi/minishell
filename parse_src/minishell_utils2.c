/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:04:33 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/10 14:48:58 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
