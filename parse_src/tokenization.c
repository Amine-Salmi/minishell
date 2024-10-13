/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/13 17:21:34 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../includes/minishell_merg.h"

// char	*ft_strlcpy(char *dst, const char *src)
// {
// 	size_t	i;

// 	if (src == 
// 	i = 0;
// 	while (src[i++])
// 		dst[i] = src[i];
// 	dst[i] = '\0';
// 	return (dst);
// }

int is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

//function to classify the type of a token
// void classify_token_type(t_con *c, char *command)
// {
// 	if (strcmp(c->command, "|") == 0)
// 		c->type = PIPE;
// 	else if (strcmp(c->command, "\"") == 0)
// 		c->type = DOUBLE_QUOTES;
// 	else if (strcmp(c->command, "'") == 0)
// 		c->type = QUOTES;
// 	else if (strcmp(c->command, " ") == 0)
// 		c->type = SPACE;
// 	else if (strcmp(c->command, "<") == 0)
// 		c->type = REDIR_IN;
// 	else if (strcmp(c->command, ">") == 0)
// 		c->type = REDIR_OUT;
// 	else if (strcmp(c->command, "<<") == 0)
// 		c->type = HERE_DOC;
// 	else if (strcmp(c->command, ">>") == 0)
// 		c->type = DREDIR_OUT;
// 	else if (strcmp(c->command, "$") == 0)
// 		c->type = ENV;
// 	else
// 		c->type = CMD;
// }

//function to add a token and reset the buffer
// void add_token(char *buffer, int *buffer_index, t_token *main, int *j)
// {
// 	if(*j == 0)
// 		main[*j].command = NULL;
// 	if (*buffer_index > 0)
// 	{
// 		buffer[*buffer_index] = '\0';
// 		main[*j].command = strdup(buffer);
// 		classify_token_type(&main[*j]);
// 		(*j)++;
// 		*buffer_index = 0;
// 	}
// }

//function to handle redir and treat herdoc
// void handle_redir_and_herdoc(const char *command, int *i, t_token *main, int *j)
// {
// 	main[*j].command = strdup(command);
// 	(*i)++;
// 	if (command[*i])
// 	{
// 		if (command[*i] == main[*j].command[0])
// 			main[*j].command = strcat(main[*j].command, command);
// 		else
// 			(*i)--;
// 	}
// 	printf("str = %s\n", main[*j].command);
// 	(*j)++;
// }

// function to handle spaces and treat multiple spaces as one
// void handle_spaces(const char *command, int *i, t_token *main, int *j)
// {
// 	while (command[*i] == ' ')
// 		(*i)++;
// 	(*i)--;
// 	main[*j].command = strdup(" ");
// 	main[*j].type = SPACE;
// 	(*j)++;
// }

// function to handle quotes as separate tokens
// void handle_quotes(char quote_type, t_token *main, int *j)
// {
	
// 	main[*j].command = malloc(2);
// 	main[*j].command[0] = quote_type;
// 	main[*j].command[1] = '\0';
// 	main[*j].type = QUOTES;
// 	(*j)++;
// }
int	is_alpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}

int	is_print(int p)
{
	if ((p <= 126 && p >= 32))
		return (1);
	return (0);
}

int	is_digit(int nb, int zero)
{
	if (zero)
	{
		if (nb == 48)
			return (1);
	}
	else
	{
		if ((nb <= 57 && nb > 48))
			return (1);
	}
	return (0);
}

// main tokenization function
// int tokenization(const char *command, t_token *main)
// {
// 	bool in_quotes = false;
// 	bool in_single_quotes = false;
// 	bool in_the_first =  true;
// 	int i = 0;
// 	int j = 0;
// 	int buffer_index = 0;
// 	char buffer[256];

// 	while (command[i])
// 	{
// 		if (command[i] == '$')
// 		{
// 			while (command[++i])
// 			{
// 				if (command[i] == '$')
// 				{
// 					buffer[buffer_index++] = command[i];
// 					add_token(buffer, &buffer_index, main, &j);
// 					in_the_first = false;
// 					i++;
// 				}
// 				if (is_digit(command[i], 1) && in_the_first)
// 				{
// 					buffer[buffer_index++] = command[i];
// 					add_token(buffer, &buffer_index, main, &j);
// 					in_the_first = false;
// 					i++;
// 				}
// 				if (is_digit(command[i], 0) && in_the_first)
// 					i++;
// 				else if (is_print(command[i]))
// 					buffer[buffer_index++] = command[i];
// 				else
// 					break ;
// 				in_the_first = false;
// 			}
// 		}
// 		if (command[i] == '"')
// 		{
// 			if (in_single_quotes == false)
// 			{
// 				in_quotes = !in_quotes;
// 				add_token(buffer, &buffer_index, main, &j);
// 				handle_quotes('"', main, &j);
// 			}
// 			else
// 				buffer[buffer_index++] = command[i];
// 		}
// 		else if (command[i] == '\'')
// 		{
// 			if (in_quotes == false)
// 			{
// 				in_single_quotes = !in_single_quotes;
// 				add_token(buffer, &buffer_index, main, &j);
// 				handle_quotes('\'', main, &j);
// 			}
// 			else
// 				buffer[buffer_index++] = command[i];
// 		}
// 		else if ((command[i] == ' ' || command[i] == '|' || is_redir(command[i])) 
// 			&& in_quotes == false && in_single_quotes == false)
// 		{
// 			add_token(buffer, &buffer_index, main, &j);
// 			if (command[i] == ' ')
// 				handle_spaces(command, &i, main, &j);
// 			else if (command[i] == '|')
// 			{
// 				main[j].command= strdup("|");
// 				main[j].cmd_type = PIPE;
// 				j++;
// 			}
// 			else if (is_redir(command[i]))
// 			{
// 				handle_redir_and_herdoc(command, &i, main, &j);
// 				add_token(buffer, &buffer_index, main, &j);
// 			}
// 		}
// 		else
// 			buffer[buffer_index++] = command[i];
// 		i++;
// 	}
// 	add_token(buffer, &buffer_index, main, &j);
// 	return j;
// }

// int main ()
// {
//     int j;
//     int i = -1;
// 	t_token		token[1000];
//     j = tokenization("ls -l>>>>'b ", token);
//     while (++i < j)
//         printf("token [%d] : %s\n", i, token[i].command);
// }