/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:41:39 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/17 02:10:04 by asalmi           ###   ########.fr       */
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
		return (ft_itoa(e->exit_status));
	while (e)
	{
		if (cmp(e->content->var, s))
			return (parse_strdup(e->content->value));
		e = e->next;
	}
	return (parse_strdup(""));
}

static char	*get_var(char *str, int size)
{
	int		i;
	char	*p;

	i = -1;
	p = malloc(size + 1);
	while (++i < size)
		p[i] = str[i];
	p[i] = '\0';
	return (p);
}

char	*__strchr(char *str, int c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i++])
	{
		size = i;
		if (str[i] == (char)c)
			return (get_var(str, size));
	}
	return (NULL);
}

bool	special_char(char c, int index)
{
	if (c == 36 && index == 1)
		return (false);
	if ((c >= 58 && c <= 64) || (c >= 1 && c <= 57))
		return (true);
	return (false);
}
