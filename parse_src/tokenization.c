/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/20 09:34:33 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_env(char *cmd)
{
	int i;

	i = 0;
	if (cmd[i] == '$')
	{
		if (cmd[i])
			i++;
		if (cmd[i] == '$')
			return (0);
		if (ft_isdigit(cmd[i]))
			return (2);
		if (cmd[i] == '\'' || cmd[i] == '\"')
			return (3);
		return (1);
	}
	else
		return (-1);
}

char	*replace_env(t_env *e, char *s)
{
	while (e)
	{
		if (cmp(e->content->var, s))
			return (parse_strdup(e->content->value));
		e = e->next;
	}
	return (parse_strdup(""));
}

char	*remove_q(char *s_command)
{
	bool	in_single_quotes;
	bool	in_quotes;
	char	*buffer;
	int		buffer_index;

	in_single_quotes = false;
	in_quotes = false;
	buffer = malloc(parse_strlen(s_command) + 1);
	int i = -1;
	buffer_index = 0;
	while (s_command[++i])
	{
		if (!in_quotes && s_command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && s_command[i] == '\"')
			in_quotes = !in_quotes;
		else
			buffer[buffer_index++] = s_command[i];
	}
	buffer[buffer_index] = '\0';
	return (buffer);
}

char	*add_token(char *buffer, int *buffer_index)
{
	char	*s;

	if (*buffer_index > 0)
	{
		buffer[*buffer_index] = '\0';
		s = parse_strdup(buffer);
		*buffer_index = 0;
	}
	return(s);
}

int	get_env_size(char *cmd, t_env *e)
{
	int		i;
	int		j;
	int		size;
	char	var_name[256];

	size = 0;
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			i++;
			j = 0;
			while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
				var_name[j++] = cmd[i++];
			size += parse_strlen(replace_env(e, var_name));
		}
		i++;
		size++;
	}
	return (size);
}

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

t_index	max_files_args(char **s_command)
{
	t_index	index;
	int		i;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	i = 0;
	while (s_command[i])
	{
		if (cmp(s_command[i], "<<"))
			index.j++;
		if (s_command[i] &&(cmp(s_command[i], "<") || cmp(s_command[i], ">") 
			|| cmp(s_command[i], ">>")))
		{
			index.i++;
			i++;	
		}
		else if (s_command[i])
			index.k++;
		i++;
	}
	return (index);
}

void	__helper_token(t_con *c, t_env *e, char *s_command, int *index)
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

void	__token(char **s_command, t_con *c, t_env *e)
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
			__helper_token(c, e, s_command[index.j], &index.i);
		}
		else if (s_command[index.j])
		{
			c->arg[index.k] =  parse_strdup(s_command[index.j]);
			index.k++;
		}
		index.j++;
	}
	c->arg[index.k] = NULL;
	free (s_command);
}
