/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:15:23 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/20 09:43:16 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (parse_strlen(s1) != parse_strlen(s2))
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	__error(char c, int i)
{
	if (i == 0)
		printf("%s\n", ARGS_ERROR);
	if (i == 1)
	{
		if (c == '\n')
			printf("42sh: syntax error near unexpected token `newline'\n");
		else
		{
			printf("42sh: syntax error near unexpected token ");
			printf("`%c'\n", c);
		}
	}
	if (i == 2)
	{
		printf("42sh: syntax error near unexpected token ");
		printf("`%c%c'\n", c, c);
	}
}

static void	__bzero(void *s, size_t n)
{
	while (n--)
		*((unsigned char *)(s + n)) = 0;
}

void	*__calloc(size_t count, size_t size)
{
	void	*res;

	res = malloc(size * count);
	if (!res)
		return (0);
	__bzero(res, size * count);
	return (res);
}

// is redir function < > >> <<
int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<'
		|| c == '$' || c == '\'')
		return (0);
	return (1);
}

void	__free(t_list **lst)
{
	t_list	*head;
	t_list	*tmp;

	if (!*lst)
		return ;
	head = *lst;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	*lst = NULL;
}
