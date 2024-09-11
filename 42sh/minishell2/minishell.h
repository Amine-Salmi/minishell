/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:11 by bbadda            #+#    #+#             */
/*   Updated: 2024/09/11 15:11:12 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

# define ARGS_ERROR  "number of arguments"

enum e_token_type
{
	WORD = 'W',
	OPTION = '-',
	SPACE = ' ',
	NEW_LINE = '\n',
	QUOTES = '\'',
	DOUBLE_QUOTES = '\"',
	ENV = '$',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	// HERE_DOC,
	// DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_token
{
	char	command[1000];
	enum e_token_type		cmd_type;
	enum e_state			state;
}t_token;

typedef struct s_split
{
	char	**list;
	char		c;
}t_split;

typedef struct s_list
{
	t_token			*content;
	struct s_list	*next;
	struct s_list	*prev;
}t_list;


char		**ft_split(char const *s, char c);
int			cmp(const char *s1, const char *s2);
char		*get_pipe(char *line);
int			ft_strlen(const char *str);
int			is_special_char(char c);
t_list		*creat_list(t_token *is);
void		add_list_back(t_list **lst, t_token *is);
void	    __error(char c, int i);
// --------------------tokenization_functions-----------------//
int			tokenization(char *command, t_token	*token);
int			classify_token_type(t_token *token);
// --------------------syntax_error_functions-----------------//
int			syntax_error(t_token *token, int j);
int			qoutes_error(t_token *token, int j);
int			pipe_error(t_token *token, int j);


void print_full_command(int j, t_token *token);

#endif