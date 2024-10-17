/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/17 17:25:55 by asalmi           ###   ########.fr       */
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
			return (strdup(e->content->value));
		e = e->next;
	}
	return (s);
}

char	*remove_q(char *s_command)
{
	bool	in_single_quotes = false;
	bool	in_quotes = false;
	char	*buffer;
	int		buffer_index;
	
	int i = -1;
	buffer_index = 0;
	while (s_command[++i])
	{
		printf("c[i] = %c\n", s_command[i]);
		if (!in_quotes && s_command[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (!in_single_quotes && s_command[i] == '\"')
			in_quotes = !in_quotes;
		else
			buffer[buffer_index++] = s_command[i];
	}
	return (buffer);
}
char	*check_and_replace_env(char *s_command, t_env *e)
{
	int i = -1;
	while (s_command[++i])
	{
		if (s_command[i] == '$')
		{
			if (check_env(s_command) == 1)
				s_command = parse_strdup(replace_env(e, s_command + 1));
			if (check_env(s_command) == 0)
				s_command = parse_strdup(s_command + 1);
			if (check_env(s_command) == 2)
				s_command = parse_strdup(s_command + 2);
			if (check_env(s_command) == 3)
				printf("baaad env \n");
		}
	}
	return (s_command);
}

t_index	max_files_args(char **s_command)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (s_command[index.j])
	{
		if (s_command[index.j] &&(cmp(s_command[index.j], "<") || cmp(s_command[index.j], ">") 
			|| cmp(s_command[index.j], "<<") || cmp(s_command[index.j], ">>")))
		{
			index.i++;
			index.j++;	
		}
		else if (s_command[index.j])
			index.k++;
		if (s_command[index.j])
			index.j++;
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
		printf("s1 = %s\n", s_command[index.j]);
		s_command[index.j] = check_and_replace_env(s_command[index.j], e);
		printf("s2 = %s\n", s_command[index.j]);
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
