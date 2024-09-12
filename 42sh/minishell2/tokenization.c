/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:05 by bbadda            #+#    #+#             */
/*   Updated: 2024/09/12 15:43:21 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir(char c)
{
    if (c == '>' || c == '<')
        return (1);
    return (0);
}

//function to classify the type of a token
void classify_token_type(t_token *token)
{
    if (strcmp(token->command, "|") == 0)
        token->cmd_type = PIPE;
    else if (strcmp(token->command, "\"") == 0 || strcmp(token->command, "'") == 0)
        token->cmd_type = QUOTES;
    else if (strcmp(token->command, " ") == 0)
        token->cmd_type = SPACE;
    else if (strcmp(token->command, "<") == 0)
        token->cmd_type = REDIR_IN;
    else if (strcmp(token->command, ">") == 0)
        token->cmd_type = REDIR_OUT;
    else if (strcmp(token->command, "<<") == 0)
        token->cmd_type = HERE_DOC;
    else if (strcmp(token->command, ">>") == 0)
        token->cmd_type = DREDIR_OUT;
    else
        token->cmd_type = WORD;
}

//function to add a token and reset the buffer
void add_token(char *buffer, int *buffer_index, t_token *token, int *j)
{
    if (*buffer_index > 0)
    {
        buffer[*buffer_index] = '\0';
        strcpy(token[*j].command, buffer);
        classify_token_type(&token[*j]);
        (*j)++;
        *buffer_index = 0;
    }
}

//function to handle redir and treat herdoc
void handle_redir_and_herdoc(const char *command, int *i, t_token *token, int *j)
{
    token[*j].command[0] = command[*i];
    (*i)++;
    if (command[*i] && is_redir(command[*i]))
        token[*j].command[1] = command[*i];
    token[*j].command[2] = '\0';
    (*j)++;
}

// function to handle spaces and treat multiple spaces as one
void handle_spaces(const char *command, int *i, t_token *token, int *j)
{
    while (command[*i] == ' ')
        (*i)++;
    (*i)--;
    strcpy(token[*j].command, " ");
    token[*j].cmd_type = SPACE;
    (*j)++;
}

// function to handle quotes as separate tokens
void handle_quotes(char quote_type, t_token *token, int *j)
{
    token[*j].command[0] = quote_type;
    token[*j].command[1] = '\0';
    token[*j].cmd_type = QUOTES;
    (*j)++;
}

// main tokenization function
int tokenization(const char *command, t_token *token)
{
    bool in_quotes = false;
    bool in_single_quotes = false;
    int i = 0, j = 0, buffer_index = 0;
    char buffer[256];

    while (command[i])
    {
        if (command[i] == '"')
        {
            in_quotes = !in_quotes;
            add_token(buffer, &buffer_index, token, &j);
            handle_quotes('"', token, &j);
        }
        else if (command[i] == '\'')
        {
            in_single_quotes = !in_single_quotes;
            add_token(buffer, &buffer_index, token, &j);
            handle_quotes('\'', token, &j);
        }
        else if ((command[i] == ' ' || command[i] == '|' || is_redir(command[i])) && !in_quotes && !in_single_quotes)
        {
            add_token(buffer, &buffer_index, token, &j);
            if (command[i] == ' ')
                handle_spaces(command, &i, token, &j);
            else if (command[i] == '|')
            {
                token[j].command[0] = '|';
                token[j].command[1] = '\0';
                token[j].cmd_type = PIPE;
                j++;
            }
            else if (is_redir(command[i]))
            {
                handle_redir_and_herdoc(command, &i, token, &j);
                add_token(buffer, &buffer_index, token, &j);
            }
        }
        else
            buffer[buffer_index++] = command[i];
        i++;
    }
    add_token(buffer, &buffer_index, token, &j);
    return j;
}

// int main ()
// {
//     int j;
//     int i = -1;
// 	t_token		token[1000];
//     j = tokenization("ls -l>>>>'b ", token);
//     while (++i < j)
//         printf("token [%d] : %s\n", i, token[i].command);
// }