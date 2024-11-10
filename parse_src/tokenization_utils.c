/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:23:02 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/10 14:10:04 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quotes_status(char *cmd, int *i, bool *in_sq, bool *in_quotes)
{
	if (!cmd)
		return ;
	if (!*in_quotes && cmd[*i] == '\'')
		*in_sq = !*in_sq;
	else if (!*in_sq && cmd[*i] == '\"')
		*in_quotes = !*in_quotes;
}

int	__lstsize(t_env *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	simple_free(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		free(command[i++]);
	free (command);
}
