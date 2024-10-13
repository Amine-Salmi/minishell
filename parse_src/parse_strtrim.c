/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strtrim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 09:56:40 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/13 17:21:23 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../includes/minishell_merg.h"

static int	getcheck(char str, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (str == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	getstart(char *str, char *set)
{
	int	i;

	i = 0;
	while (getcheck(str[i], set) == 1)
		i++;
	return (i);
}

static int	getend(char *str, char *set)
{
	int	i;

	i = parse_strlen(str) - 1;
	while (getcheck(str[i], set) == 1)
		i--;
	return (i);
}

char	*parse_strtrim(char const *str, char const *set)
{
	int		len;
	char	*new_str;
	char	*dest;
	int		start;
	int		end;

	if (str == NULL || set == NULL)
		return (NULL);
	if ((str[0] == '\0' && set[0] == '\0') || str[0] == '\0')
	{
		dest = malloc(1);
		if (dest == NULL)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	end = getend((char *)str, (char *)set);
	start = getstart((char *)str, (char *)set);
	len = end - start;
	new_str = parse_substr(str, start, len + 1);
	return (new_str);
}
