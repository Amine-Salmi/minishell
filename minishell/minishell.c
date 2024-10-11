/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/11 12:39:44 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char c, bool in_quotes, bool in_single_quotes)
{
	if (!in_quotes && c == '\'')
			in_single_quotes = !in_single_quotes;
	else if (!in_single_quotes && c == '\"')
		in_quotes = !in_quotes;
}

t_index	max_files_args(char **s_command)
{
	t_index	index;

	index.i = 0;
	index.j = 1;
	index.k = 0;
	while (s_command[index.j])
	{
		if (s_command[index.j] &&(!strcmp(s_command[index.j], "<") || !strcmp(s_command[index.j], ">") 
			|| !strcmp(s_command[index.j], "<<") || !strcmp(s_command[index.j], ">>")))
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

void	__token(char **s_command, t_con *c)
{
	t_index	index;

	index.i = 0;
	index.j = 1;
	index.k = 0;
	while (s_command[index.j])
	{
		if (s_command[index.j] &&(!strcmp(s_command[index.j], "<") || !strcmp(s_command[index.j], ">") 
			|| !strcmp(s_command[index.j], "<<") || !strcmp(s_command[index.j], ">>")))
		{
			c->file[index.i ].opr = strdup(s_command[index.j]);
			index.j++;
			if (s_command[index.j])
				c->file[index.i ].file_name = strdup(s_command[index.j]);
			index.i++;
		}
		else if (s_command[index.j])
		{
			c->arg[index.k]=  strdup(s_command[index.j]);
			index.k++;
		}
		if (s_command[index.j])
			index.j++;	
	}
	c->file[index.i ].opr = NULL;
	c->arg[index.k] = NULL;
}

t_token	*toke_lexer(char **command, t_token *token)
{
	int		i;
	t_con	c;
	char	**s_command;
	char	*s;
	t_index	index;
	
	token = NULL;
	i = -1;
	while (command[++i])
	{
		s = add_spaces(command[i]);
		syntax_error(s);
		s_command = ft_split(s, ' ');
		free(s);
		index = max_files_args(s_command);
		c.file = malloc(index.i * sizeof(t_opr));
		c.arg = malloc(index.k *sizeof(char *));
		c.file[0].opr = NULL;
		c.arg[0] = NULL;
		if (!__is_herdoc(s_command[0]))
			c.command = s_command[0];
		__token(s_command, &c);
		add_list_back(&token, &c);
	}
	return (token);
}

void	priiint(t_token *token)
{
	while (token)
	{
		int i = 0;
		printf("command : %s\n", token->command);
		while (token->arg[i])
		{
			printf("arg[%d] : %s\n", i, token->arg[i]);
			// if (token->prev)
			// 	printf("prev arg[%d] : %s\n", i, token->prev->arg[i]);
			i++;
		}
		int j = 0;
		while (token->file[j].opr)
		{
			printf("file name[%d] : %s\n", j, token->file[j].file_name);
			printf("opr[%d] : %s\n", j, token->file[j].opr);
			// if (token->prev)
			// 	printf("prev namefile[%d] : %s\n", j, token->prev->file[j].file_name);
			j++;
		}
		token = token->next;
	}
}

// tokenization
// check syntax error
// expended
// change $user by user define
// move "" and ''
int main (int ac, char *av[], char **env)
{
	char		**command;
	char		*full_command;
	t_token		*token;
	t_con		*c;
	t_env		*e;

	e = NULL;
	e = (t_env *)malloc(sizeof(t_env));
	token = (t_token *)malloc(sizeof(t_token));
	c = (t_con *)malloc(sizeof(t_con));
	while (1)
	{
		e = get_env(env);
		full_command = readline("⑉➤minishell-$");
		add_history(full_command);
		if (pipe_error(full_command, ft_strlen(full_command)))
			continue ;
		command = ft_split(full_command, '|');
		token = toke_lexer(command, token);
		priiint(token);
	}
	return (0);
}
