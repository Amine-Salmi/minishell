/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/24 13:14:51 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		else if (s_command[i] &&(cmp(s_command[i], "<") || cmp(s_command[i], ">") 
			|| cmp(s_command[i], ">>")))
			index.i++;
		else if (s_command[i])
			index.k++;
		i++;
	}
	return (index);
}

t_token	*toke_lexer(char **command, t_token *token, t_env *e)
{
	int		i;
	int 	size;
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
		s_command = parse_split(s, ' ');
		free(s);
		index = max_files_args(s_command);
		if (index.i + index.j > 0)
			c.file = malloc((index.i + index.j) * sizeof(t_opr));
		c.file[i].del = NULL;
		// c.file[i].file_name = NULL;
		// c.file[i].opr = NULL;
		if (index.k > 0)
			c.arg = malloc((index.k + 1) * sizeof(char *));
		if (!c.arg || !c.file)
			return (NULL);
		if (!__is_herdoc(s_command[0]))
			c.command = remove_q(s_command[0]);
		else
			c.command = NULL;
		__token(s_command, &c, e, index.j, index.i);
		size = index.i + index.j;
		add_list_back(&token, c, size);
	}
	return (token);
}

void	priiint(t_token *token)
{
	int	i;
	int	j;

	while (token)
	{
		i = 0;
		if (token->command)
			printf("command : %s\n", token->command);
		while (token->arg[i])
		{
			printf("arg[%d] : %s\n", i, token->arg[i]);
			i++;
		}
		j = 0;
		printf("d=d====   %d\n", token->number_of_file);
		while (j < token->number_of_file)
		{
			printf("opr[%d] : %s\n", j, token->file[j].opr);
			if (token->file[j].del)
			{
				printf("in del :: j = %d\n", j);
				printf("and------ %s\n",token->file[j].del);
				printf("del[%d] : %s\n", j, token->file[j].del);
				
			}
			if (token->file[j].file_name)
			{
				printf("in f name :: j = %d\n", j);
				printf("file name[%d] : %s\n", j, token->file[j].file_name);
			}
			j++;
		}
		token = token->next;
	}
}

int main (int ac, char *av[], char **env)
{
	(void)av;
	(void)ac;

	char		**command;
	char		*full_command;
	t_token		*token;
	t_con		*c;
	t_env		*my_env;

	my_env = NULL;
	my_env = (t_env *)malloc(sizeof(t_env));
	token = (t_token *)malloc(sizeof(t_token));
	c = (t_con *)malloc(sizeof(t_con));
	my_env = get_env(env);
	while (1)
	{
		full_command = readline("\033[1;31m-\033[0m  \033[1;32mminishell-0.1$\033[0m ");
		if (!full_command)
			break;
		add_history(full_command);
		if (pipe_error(full_command, parse_strlen(full_command)))
			continue ;
		command = parse_split(full_command, '|');
		token = toke_lexer(command, token, my_env);
		// printf("=============================\n");
		// printf("file: %p\n", token->file);
		// printf("file name : %s\n", token->file->file_name);
		// printf("opr : %s\n", token->file->opr);
		// printf("del : %s\n", token->file->del);
		// printf("=============================\n");
		// if (token)
			// ft_execute(token, &my_env);
		priiint(token);
		free(full_command);
	}
	return (0);
}
