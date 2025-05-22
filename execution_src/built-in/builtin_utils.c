/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:30:10 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/17 01:47:49 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	count_word(const char *s)
{
	size_t	count_word;
	int		found_eq;
	int		i;

	count_word = 1;
	found_eq = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			found_eq = 1;
			break ;
		}
		i++;
	}
	if (found_eq)
		count_word = 2;
	return (count_word);
}

static void	free_array_words(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static char	**ft_alocated(char **array, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[j] && s[j] != c)
		j++;
	array[i] = ft_substr(s, 0, j);
	if (!(array[i]))
	{
		free_array_words(i, array);
		return (NULL);
	}
	i++;
	if (s[j] && s[j] == c)
		j++;
	array[i] = ft_substr(s, j, (ft_strlen(s) - j));
	if (!(array[i]))
	{
		free_array_words(i, array);
		return (NULL);
	}
	array[++i] = 0;
	return (array);
}

char	**split_first_eq(char const *s, char c)
{
	char	**list;
	int		words;

	if (!s)
		return (NULL);
	words = count_word(s);
	list = (char **)malloc(sizeof(char *) * (words + 1));
	if (!list)
		return (NULL);
	if (words == 1)
	{
		list[0] = ft_strdup(s);
		if (!list[0])
			return (NULL);
		list[1] = NULL;
	}
	else
		list = ft_alocated(list, s, c);
	return (list);
}
