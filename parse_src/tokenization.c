/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/10 17:45:19 by bbadda           ###   ########.fr       */
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

bool	check_if_pair(char *cmd, int *i, bool *pair)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] == '$')
	{
		*pair = !*pair;
		(*i)++;
	}
	return (*pair);
}

void	handle_dollar_sign(char *cmd, int *i, t_env *e, char *buffer, int *buffer_index)
{
	bool	in_the_first;
	bool	pair;
	char	var_name[256];
	char	*value;
	int		j;

	in_the_first = true;
	pair = true;
	check_if_pair(cmd, i, &pair);
	if (pair)
	{
		extract_var_name(cmd, i, var_name, &in_the_first);
		value = replace_env(e, var_name);
		if (value)
		{
			j = 0;
			while (value[j])
				buffer[(*buffer_index)++] = value[j++];
			free(value);
		}
	}
}

char	*__env(char *cmd, t_env *e)
{
	char		*buffer;
	int			buffer_index;
	int			i;
	bool		in_single_quotes;
	bool		in_quotes;

	in_single_quotes = false;
	in_quotes = false;
	i = 0;
	buffer_index = 0;
	buffer = __calloc(get_env_size(cmd, e) + 1, 1);
	while (cmd[i])
	{
		quotes_status(cmd, &i, &in_single_quotes, &in_quotes);
		if (cmd[i + 1] && cmd[i] == '$'
			&& cmd[i + 1] != ' ' && !in_single_quotes && cmd[i + 1] != '\"')
			handle_dollar_sign(cmd, &i, e, buffer, &buffer_index);
		else
			buffer[buffer_index++] = cmd[i++];
		buffer[buffer_index] = '\0';
	}
	return (remove_q(buffer));
}

void	__check_herdoc_expend(char *cmd, bool *expend)
{
	if (cmd[0] == '\"' || cmd[0] == '\'')
		*expend = false;
}

void	__token(t_token *token, char **cmd, t_env *e)
{
	t_index		index;
	char		*str;
	bool		b;

	b = true;
	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (cmd[index.j] && parse_strlen(cmd[index.j]) > 0)
	{
		str = __env(cmd[index.j], e);
		if (cmp(str, "<<"))
		{
			// char *sc = __env(cmd[++index.j], e);
			index.j++;
			char *tt = parse_strdup(cmd[index.j]);
			__check_herdoc_expend(tt, &b);
			char *f = remove_q(tt);
			__add_back_herdoc(&token->herdoc, str, f, b);
			free (f);
		}
		else if ((cmp(str, "<") || cmp(str, ">") || cmp(str, ">>")))
		{
			char *scfae = __env(cmd[++index.j], e);
			__add_back_file(&token->file, scfae, str);
			free (scfae);
		}
		else
		{
			if (!token->command)
				token->command = __env(str, e);
			token->arg[index.k] = parse_strdup(str);
			index.k++;
		}
		free(str);
		token->arg[index.k] = NULL;
		index.j++;
	}
}
