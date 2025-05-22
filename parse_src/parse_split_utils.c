/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:23:46 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/12 04:23:48 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
}

int	parse_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*parse_strdup(const char *src)
{
	char	*dst;
	int		i;
	int		len; 

	i = -1;
	len = parse_strlen(src);
	dst = (char *)malloc(len + 1);
	if (dst == 0)
		return (NULL);
	while (++i < len)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*parse_substr(char const *str, int start, int len)
{
	char	*sub;
	int		i;

	if (!str)
		return (NULL);
	if (start > parse_strlen(str))
		return (parse_strdup(""));
	if (len > parse_strlen(str) - start)
		len = parse_strlen(str) - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = str[start];
		i++;
		start ++;
	}
	sub[i] = '\0';
	return (sub);
}
