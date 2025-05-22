/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/13 02:07:07 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	extract_var_name(char *cmd, int *i, char *var_name, bool *in_the_first)
{
	int	j;

	j = 0;
	while (cmd[*i])
	{
		if ((ft_isdigit(cmd[*i]) || cmd[*i] == '?') && *in_the_first)
		{
			var_name[j++] = cmd[(*i)++];
			break ;
		}
		else if (ft_isalnum(cmd[*i]) || cmd[*i] == '_')
			var_name[j++] = cmd[(*i)++];
		else
			break ;
		*in_the_first = false;
	}
	var_name[j] = '\0';
}

static void	__create_herdoc_list(t_token *token, t_buffer str, bool *e, int *i)
{
	char	*s;
	char	*s2;

	(*i)++;
	s = parse_strdup(str.cmd2[*i]);
	if (s[0] == '\"' || s[0] == '\'')
		*e = false;
	s2 = remove_q(s);
	__add_back_herdoc(&token->herdoc, str.str, s2, e);
	free(s2);
}

static void	__create_file_list(t_token *token, t_buffer str, int *i, t_env *e)
{
	char	*s;

	s = __env(str.cmd2[++(*i)], e);
	__add_back_file(&token->file, s, str.str);
	free (s);
}

static void	init_data(int *j, int *k, bool *expend)
{
	*expend = true;
	*j = 0;
	*k = 0;
}

void	__token(t_token *token, char **cmd, t_env *e)
{
	t_index		index;
	bool		expend;
	t_buffer	string;

	init_data(&index.j, &index.k, &expend);
	string.cmd2 = cmd;
	while (string.cmd2[index.j] && parse_strlen(string.cmd2 [index.j]) > 0)
	{
		string.str = __env(string.cmd2 [index.j], e);
		if (cmp(string.str, "<<"))
			__create_herdoc_list(token, string, &expend, &index.j);
		else if ((cmp(string.str, "<") || cmp(string.str, ">")
				|| cmp(string.str, ">>")))
			__create_file_list(token, string, &index.j, e);
		else
		{
			if (!token->command)
				token->command = __env(string.str, e);
			token->arg[index.k++] = parse_strdup(string.str);
		}
		free(string.str);
		token->arg[index.k] = NULL;
		index.j++;
	}
}
