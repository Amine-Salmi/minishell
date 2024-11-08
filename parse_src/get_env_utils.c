/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:41:39 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/08 20:22:18 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_env(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '$')
	{
		if (cmd[i])
			i++;
		if (cmd[i] == '$')
			return (0);
		if (ft_isdigit(cmd[i]))
			return (2);
		if (cmd[i] == '\'' || cmd[i] == '\"')
			return (3);
		return (1);
	}
	else
		return (-1);
}

char	*replace_env(t_env *e, char *s)
{
	if (cmp("?", s))
		return (parse_strdup(ft_itoa(e->exit_status)));
	while (e)
	{
		if (cmp(e->content->var, s))
			return (parse_strdup(e->content->value));
		e = e->next;
	}
	return (parse_strdup(""));
}
