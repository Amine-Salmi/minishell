/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:46:55 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/12 05:55:32 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_index	max_files_args(char **s_command)
{
	t_index	index;
	int		i;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	i = 0;
	while (s_command[i])
	{
		if (cmp(s_command[i], "<<"))
			index.j++;
		else if (s_command[i] && (cmp(s_command[i], "<")
				|| cmp(s_command[i], ">") || cmp(s_command[i], ">>")))
			index.i++;
		else if (s_command[i])
			index.k++;
		i++;
	}
	return (index);
}

void	allocate_for_me(t_index index, t_token *token)
{
	if (index.j > 0)
	{
		token->herdoc = malloc(index.j * sizeof(t_herdoc));
		token->herdoc->del = NULL;
		token->herdoc->herdoc = NULL;
		token->herdoc->expend = 1;
	}
	if (index.i > 0)
	{
		token->file = malloc(index.i * sizeof(t_opr));
		token->file->file_name = NULL;
		token->file->opr = NULL;
	}
	if (index.k > 0)
		token->arg = malloc((index.k + 1) * sizeof(char *));
}

void	__put_and_exit(t_env *my_env)
{
	ft_putstr_fd("exit\n", 1);
	exit(my_env->exit_status);
}
