/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/22 13:20:38 by bbadda           ###   ########.fr       */
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

void	__helper_token(t_con *c, t_env *e, char *s_command, int *index, int nbr_d)
{
	if (s_command)
	{
		if (cmp(c->file[*index].opr, "<<"))
			c->file[*index].del = parse_strdup(check_and_replace_env(s_command, e));
		else
			c->file[*index].file_name = parse_strdup(check_and_replace_env(s_command, e));
		(*index)++;
	}
}

void	__token(char **s_command, t_con *c, t_env *e, int nbr_d, int nbr_f)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (s_command[index.j])
	{
		s_command[index.j] = check_and_replace_env(s_command[index.j], e);
		if (s_command[index.j] && (cmp(s_command[index.j], "<") || cmp(s_command[index.j], ">") 
			|| cmp(s_command[index.j], "<<") || cmp(s_command[index.j], ">>")))
		{
			c->file[index.i].opr = parse_strdup(s_command[index.j]);
			index.j++;
			__helper_token(c, e, s_command[index.j], &index.i, nbr_d);
		}
		else if (s_command[index.j])
		{
			c->arg[index.k] =  parse_strdup(s_command[index.j]);
			index.k++;
		}
		index.j++;
	}
	printf("nbr_d %d and nbr_f %d\n", nbr_d, nbr_f);
	c->arg[index.k] = NULL;
	c->file[nbr_d].del = NULL;
	c->file[nbr_f].file_name = NULL;
	c->file[index.j].opr = NULL;
	free (s_command);
}
