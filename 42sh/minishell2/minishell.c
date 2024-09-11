/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/09/11 15:33:39 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_full_command(int j, t_token *token)
{
	int i = 0;
	int r;
	printf(" ______________________________________________________");
	printf("________________________________________________________ \n");
   for (int k = 0; k < j; k++)
   {
		r = ft_strlen(token[k].command);
		printf("|                          |                          |");
		printf("                           |                            |\n");
		printf("|Token[%d] : '%s'", k, token[k].command);
		while (i++ < 13 - ft_strlen(token[k].command))
			printf(" ");
		i = 0;
		printf("|");
		printf("Token_type : '%c'", token[k].cmd_type);
		while (i++ < 12)
			printf(" ");
		while (r > 9)
		{
			r = r / 10;
			printf(" ");
		}
		i = 0;
		printf("|");
		printf("Len : %d",  ft_strlen(token[k].command));
		while (i++ < 19 - ft_strlen(token[k].command))
			printf(" ");
		while (r > 9)
		{
			r = r / 10;
			printf(" ");
		}
		i = 0;
		printf("|");
		printf("State : %s", "GLOBAL");
		printf("              |\n");
		printf("|__________________________|__________________________|");
		printf("___________________________|____________________________| \n");
   }
}


int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<'
		|| c == '$' || c == '\'')
		return (0);
	return (1);
}

int	classify_token_type(t_token *token)
{
	if (strcmp(token->command, "|") == 0)
		token->cmd_type = PIPE;
	else if (token->command[0] == '-')
		token->cmd_type = OPTION;
	else if (strcmp(token->command, ">") == 0)
		token->cmd_type = REDIR_OUT;
	else if (strcmp(token->command, "<") == 0)
		token->cmd_type = REDIR_IN;
	else if (token->command[0] == '$')
		token->cmd_type = ENV;
	else
		token->cmd_type = WORD;
	return (0);
}

// |, >, <,>>,<<, $, ‘ ‘
int	tokenization(char *command, t_token	*token)
{
	bool			in_quotes;
	bool			in_singel_quotes;
	int				i;
	int				j;
	int				buffer_index;
	char			*buffer;

	i = 0;
	j = 0;
	buffer_index = 0;
	in_quotes = false;
	in_singel_quotes = false;
	buffer = (char *)malloc(ft_strlen(command) + 1);
	printf("\033[32mFull size = %d.\033[00m \033[40m\n",ft_strlen(command));
	while (command[i])
	{
		if (command[i] == '"')
			in_quotes = !in_quotes;
		if (command[i] == '\'')
			in_singel_quotes = !in_singel_quotes;
		if ((command[i] == ' ' || command[i] == '|') && !in_quotes && !in_singel_quotes)
		{
			if (buffer_index > 0)
			{
				buffer[buffer_index] = '\0';
				strcpy(token[j].command, buffer);
				classify_token_type(&token[j]);
				j++;
				buffer_index = 0;
			}
			if (command[i] == ' ')
			{
				token[j].command[0] = ' ';
				token[j].command[1] = '\0';
				token[j].cmd_type = SPACE;
				j++;
			}
			if (command[i] == '|')
			{
				token[j].command[0] = '|';
				token[j].command[1] = '\0';
				token[j].cmd_type = PIPE;
				j++;
			}
		}
		else
			buffer[buffer_index++] = command[i];
		i++;
	}
	if (buffer_index > 0)
	{
		buffer[buffer_index] = '\0';
		strcpy(token[j].command, buffer);
		classify_token_type(&token[j]);
		j++;
	}
	return (j);
	free(buffer);
}

// tokenization
// check syntax error
// expended
// change $user by user define
// move "" and ''
int main (void)
{
	t_token		*is;
	int 		i;
	int 		j;
	char 		**str;
	char 		**s;
	char		*command;
	t_token		token[1000];
	t_

	while (1)
	{
		command = readline("⑉➤minishell-$");
		add_history(command);
		j = tokenization(command, token);
		// print_full_command(j, token);
		if (syntax_error(token, j))
			return (0);
	}
	return (0);
}
