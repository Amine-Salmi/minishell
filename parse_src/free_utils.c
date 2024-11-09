/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:47:24 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/09 19:06:11 by bbadda           ###   ########.fr       */
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
	t_opr	*next_add;
	tmp = opr;
	while (tmp)
	{
		free(tmp->file_name);
		free(tmp->opr);
		next_add = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = next_add;
	}
}

void	free_herdoc(t_herdoc *herdoc)
{
	t_herdoc	*tmp;
	t_herdoc	*next_add;

	tmp = herdoc;
	while (tmp)
	{
		free(tmp->herdoc);
		free(tmp->del);
		next_add = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = next_add;
	}
}

void	free_token(t_token *token)
{
	int	i;

	i = 0;
	if (token) 
	{
		free(token->command);
		while (token->arg[i])
			free(token->arg[i++]);
		free(token->arg);
		free_opr(token->file);
		free_herdoc(token->herdoc);
		free(token);
		token = NULL;
	}
}

void	free_lst(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*next_add;

	tmp = lst;
	while (tmp)
	{
		free_token(tmp->token);
		next_add = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = next_add;
	}
}

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next_add;

	tmp = *env;
	while (tmp)
	{
		free(tmp->content->var);
		free(tmp->content->value);
		free(tmp->content);
		next_add = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = next_add;
	}
	free(tmp);
}
