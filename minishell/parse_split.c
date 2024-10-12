/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:27:02 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/12 21:31:32 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
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

char	*parse_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

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
	return ((char *)sub);
}

static int	count_word(char *s, char set)
{
	bool in_quotes = false;
	bool in_single_quotes = false;
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == set && s[i])
		i++;
	if(s[0])
		count++;
	while (s[i])
	{
		if (!in_quotes && s[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && s[i] == '\"')
			in_quotes = !in_quotes;
		if (s[i] && s[i] == set && !in_single_quotes && !in_quotes)
		{
			while (s[i + 1] && s[i + 1] == set)
				i++;
			if (s[i + 1])
				count++;
		}
		i++;
	}
	return (count);
}

static int	len_word(char *s, char set, int start)
{
	bool in_quotes = false;
	bool in_single_quotes = false;
	int	i;

	i = 0;
	while (s[start])
	{
		if(s[start] == set && (!in_single_quotes && !in_quotes))
			break;
		if (!in_quotes && s[start] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && s[start] == '\"')
			in_quotes = !in_quotes;
		start++;
		i++;
	}
	return (i);
}

static void	free_list(char **list)
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

static char	**str_alloc(char const *s, char c, int fix_c, char **list)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (i < fix_c)
	{
		while (s[start] == c && s[start])
			start++;
		end = len_word((char *)s, c, start);
		list[i] = parse_substr(s, start, end);
		if (!list[i])
		{
			free_list(list);
			return (NULL);
		}
		start = start + end;
		i++;
	}
	list[i] = NULL;
	return (list);
}

char	**parse_split(char const *s, char c)
{
	char	**list;
	int		fix_c;

	if (!s)
		return (NULL);
	fix_c = count_word((char *)s, c);
	list = (char **)malloc((fix_c + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	list = str_alloc(s, c, fix_c, list);
	return (list);
}