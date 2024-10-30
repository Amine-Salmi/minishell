/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:54:38 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/30 19:21:28 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_opr	*creatlist(char *file_name, char *opr)
{
	t_opr	*node;

	node = malloc(sizeof(t_opr));
	if (!node)
		return (NULL);
	node->file_name = parse_strdup(file_name);
    node->opr = parse_strdup(opr);
	node->next = NULL;
	return (node);
}

void	__add_back_file(t_opr **file, char *file_name, char *opr)
{
	t_opr	*tmp;
	t_opr	*new;


	new = creatlist(file_name, opr);
	if (new && file)
	{

		if ((*file)->file_name == NULL)
			*file = new;
		else
		{
			tmp = *file;
			while (tmp->next )
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

t_herdoc	*creatlist_herdoc(char *herdoc, char *del)
{
	t_herdoc	*node;

	node = malloc(sizeof(t_herdoc));
	if (!node)
		return (NULL);
	node->herdoc = parse_strdup(herdoc);
    node->del = parse_strdup(del);
	node->next = NULL;
	return (node);
}

void	__add_back_herdoc(t_herdoc **herdoc, char *her, char *del)
{
	t_herdoc	*tmp;
	t_herdoc	*new;

	new = creatlist_herdoc(her, del);
	if (new && herdoc)
	{
		if ((*herdoc)->herdoc == NULL)
			*herdoc = new;
		else
		{
			tmp = *herdoc;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}
