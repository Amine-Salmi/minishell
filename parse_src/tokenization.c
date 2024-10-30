/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/30 22:52:40 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_and_replace_env(char *cmd, t_env *e)
{
	bool	in_single_quotes;
	bool	in_quotes;
	bool	in_the_first;
	bool	pair;
	char 	*buffer;
	char 	*value;
	char	var_name[256];
	int		buffer_index;
	int		i;
	int		j;

	pair = true;
	in_single_quotes = false;
	in_quotes = false;
	in_the_first = true;
	buffer = malloc(get_env_size(cmd, e) + 1);
	buffer_index = 0;
	i = 0;
	while (cmd[i])
	{
		if (!in_quotes && cmd[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && cmd[i] == '\"')
			in_quotes = !in_quotes;
		if (cmd[i] == '$' && !in_single_quotes)
		{
			i++;
			while (cmd[i] && cmd[i] == '$')
			{
				pair = !pair;
				i++;
			}
			if (pair)
			{
				j = 0;
				while (cmd[i])
				{
					if ((ft_isdigit(cmd[i]) || cmd[i] == '?') && in_the_first)
					{
						var_name[j++] = cmd[i++];
						break;
					}
					else if (ft_isalnum(cmd[i]) || cmd[i] == '_')
						var_name[j++] = cmd[i++];
					else
						break ;
					in_the_first = false;
				}
				var_name[j] = '\0';
				value = replace_env(e, var_name);
				if (value)
				{
					strcpy(&buffer[buffer_index], value);
					buffer_index += parse_strlen(value);
					free(value);
				}
			}
		}
		else
			buffer[buffer_index++] = cmd[i++];
	}
	buffer[buffer_index] = '\0';
	return (remove_q(buffer));
}


void	fill_arg(t_token *token, char *s_command, int *index)
{
	if (s_command)
	{
		token->arg[*index] =  parse_strdup(s_command);
		(*index)++;
	}
}

void	__token(t_token *token, char **s_command, t_env *e, int nbr_d, int nbr_f)
{
	t_index	index;
	int 	i;
	char	*str;
	
	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (s_command[index.j])
	{
		str = check_and_replace_env(s_command[index.j], e);
		if (cmp(str, "<<"))
			__add_back_herdoc(&token->herdoc, str, check_and_replace_env(s_command[++index.j], e));
		else if ((cmp(str, "<") || cmp(str, ">") || cmp(str, ">>")))
			__add_back_file(&token->file, check_and_replace_env(s_command[++index.j], e), str);
		else
			fill_arg(token, str, &index.k);
		free(str);
		index.j++;
	}
	token->arg[index.k] = NULL;
	free (s_command);
}
