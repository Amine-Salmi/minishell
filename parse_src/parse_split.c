/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:27:02 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/02 22:41:32 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	helper_function(char *s, int *i, char set, int *count)
{
	while (s[*i] == set && s[*i])
		(*i)++;
	if (s[0])
		(*count)++;
}

static int	count_word(char *s, char set)
{
	bool	in_quotes;
	bool	in_single_quotes;
	int		i;
	int		count;

	in_quotes = false;
	in_single_quotes = false;
	i = -1;
	count = 0;
	helper_function(s, &i, set, &count);
	while (s[++i])
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
	}
	return (count);
}

static int	len_word(char *s, char set, int start)
{
	bool	in_quotes;
	bool	in_single_quotes;
	int		i;

	in_quotes = false;
	in_single_quotes = false;
	i = 0;
	while (s[start])
	{
		if (s[start] == set && (!in_single_quotes && !in_quotes))
			break ;
		if (!in_quotes && s[start] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && s[start] == '\"')
			in_quotes = !in_quotes;
		start++;
		i++;
	}
	return (i);
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
	int		c_word;

	if (!s)
		return (NULL);
	c_word = count_word((char *)s, c);
	list = (char **)malloc((c_word + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	list = str_alloc(s, c, c_word, list);
	return (list);
}
