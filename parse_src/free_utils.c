/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:47:24 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/03 16:22:33 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	simple_free(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		free(command[i++]);
	free (command);
}

void	free_opr(t_opr *opr)
{
	t_opr	*tmp;

	while (opr)
	{
		tmp = opr;
		opr = opr->next;
		free(tmp->opr);
		free(tmp->file_name);
		free(tmp);
	}
}

void	free_herdoc(t_herdoc *herdoc)
{
	t_herdoc	*tmp;

	while (herdoc)
	{
		tmp = herdoc;
		herdoc = herdoc->next;
		free(tmp->herdoc);
		free(tmp->del);
		free_opr(tmp->file.next);
		free(tmp);
	}
}

void	free_token(t_token *token)
{
	// arg = arg;
	// if (token) 
	// {
	// 	free(arg);
	// 		free(token->command);
	// 	while (arg && arg)
	// 	{
	// 		arg++;
	// 	}
	// 	free(token->arg);
		free_opr(token->file);
		free_herdoc(token->herdoc);
		free(token);
	// }
}

void	free_lst(t_lst *lst)
{
	t_lst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_token(tmp->token);
		free(tmp);
	}
}
