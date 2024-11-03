/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/03 16:23:28 by bbadda           ###   ########.fr       */
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

void	handle_dollar_sign(char *cmd, int *i, t_env *e, char *buffer, int *buffer_index)
{
	bool	in_the_first;
	bool	pair;
	char	var_name[256];
	int		j;
	char	*value;

	in_the_first = true;
	pair = true;
	j = 0;
	(*i)++;
	while (cmd[*i] && cmd[*i] == '$')
	{
		pair = !pair;
		(*i)++;
	}
	if (pair)
	{
		extract_var_name(cmd, i, var_name, &in_the_first);
		value = replace_env(e, var_name);
		if (value)
		{
			strcpy(&buffer[*buffer_index], value);
			*buffer_index += parse_strlen(value);
			free(value);
		}
	}
}

char	*check_and_replace_env(char *cmd, t_env *e)
{
	char	*buffer;
	int		buffer_index;
	int		i;
	bool	in_single_quotes;
	bool	in_quotes;

	in_single_quotes = false;
	in_quotes = false;
	i = 0;
	buffer_index = 0;
	buffer = malloc(get_env_size(cmd, e) + 1);
	while (cmd[i])
	{
		quotes_status(cmd, &i, &in_single_quotes, &in_quotes);
		if (cmd[i + 1] && cmd[i] == '$' && cmd[i + 1] != ' ' && !in_single_quotes)
			handle_dollar_sign(cmd, &i, e, buffer, &buffer_index);
		else
			buffer[buffer_index++] = cmd[i++];
	}
	buffer[buffer_index] = '\0';
	return (remove_q(buffer));
}

void	__token(t_token *token, char **s_command, t_env *e)
{
	t_index		index;
	int			i;
	char		*str;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (s_command[index.j] && parse_strlen(s_command[index.j]) > 0)
	{
		str = check_and_replace_env(s_command[index.j], e);
		if (cmp(str, "<<"))
			__add_back_herdoc(&token->herdoc, str, check_and_replace_env(s_command[++index.j], e));
		else if ((cmp(str, "<") || cmp(str, ">") || cmp(str, ">>")))
			__add_back_file(&token->file, check_and_replace_env(s_command[++index.j], e), str);
		else
		{
			if (!token->command)
				token->command = check_and_replace_env(str, e);
			token->arg[index.k] = parse_strdup(str);
			index.k++;
		}
		token->arg[index.k] = NULL;
		free(str);
		index.j++;
	}
}
