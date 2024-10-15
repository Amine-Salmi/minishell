/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:11 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/16 00:16:21 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../lib/Libft/libft.h"

# define ARGS_ERROR  "number of arguments"

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
}t_index;

enum e_token_type
{
	CMD = 1,
	ARG = 2,
	SPACE = 3,
	NEW_LINE = 4,
	QUOTES = 5,
	DOUBLE_QUOTES = 6,
	ENV = 7,
	PIPE = 8,
	REDIR_IN = 9,
	REDIR_OUT = 10,
	HERE_DOC = 11,
	DREDIR_OUT = 12,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_opr
{
	char	*file_name;
	char	*opr;
	// char	*del;
}t_opr;

typedef struct s_con 
{	
	char	*command;
	char	**arg;
	t_opr	*file;
}t_con;


typedef struct s_token
{
	char				*command;
	char				**arg;
	t_opr				*file;
	pid_t				pid;
	struct s_token		*next;
	struct s_token		*prev;
}t_token;

// workiingg

typedef struct s_minishell
{
	char	**cmd;
	t_opr	opr;
}t_minishell;
// workiingg

// for env
typedef struct s_content 
{
	char *var;
	char *value;
}t_content;

typedef struct s_env 
{
	t_content *content;
	struct s_env *next;
}t_env;
// for env
typedef struct s_split
{
	char	**list;
	char		c;
}t_split;

// typedef struct s_list
// {
// 	t_token			*content;
// 	struct s_list	*next;
// 	struct s_list	*prev;
// }t_list;


int			cmp(const char *s1, const char *s2);
char		*get_pipe(char *line);
int			is_special_char(char c);
t_token		*creat_list(char *command, char **arg, t_opr *file);
void		add_list_back(t_token **token, t_con *c);
void	    __error(char c, int i);
void		*__calloc(size_t count, size_t size);
int			is_special_char(char c);
void		check_quotes(char c, bool in_quotes, bool in_single_quotes);
// --------------------tokenization_functions-----------------//
void		__token(char **s_command, t_con *c, t_env *e);
t_index		max_files_args(char **s_command);
char		*replace_env(t_env *e, char *s);
int		check_env(char *cmd);
char		*check_and_replace_env(char *s_command, t_env *e);

// --------------------syntax_error_functions-----------------//
int			syntax_error(char *command);
int			qoutes_error(char *command);
void		__free(t_list **lst);
// ---------------------get_env_function----------------------//
t_env   	*get_env( char **env);

// --------------------add_spaces----------------------------//
char		*add_spaces(char *cmd);
int 		__is_redir(char c);
int 		__is_herdoc(char *s);
int			pipe_error(char *command, int j);
// -------------------libft-----------------------------------//
int			parse_strlen(const char *str);
char		*parse_substr(char const *str,int start, int len);
char		**parse_split(char const *s, char c);;
char		*parse_strtrim(char const *str, char const *set);
char		*parse_strdup(const char *src);

// void 		print_full_command(int j, t_token *token);

// -------------------- executions functions ------------------ //
// ------------------------------------------------------------ //

char     *find_var_env(t_env *env, char *var);
char    *find_executable_file(char *command, char *path);
char	**copy_env(t_env *env);
void	execute_piped_commands(t_token *cmd, t_env *env);

void    redirection_handler(t_token *cmd);
// void    handle_heredoc(t_token *cmd);

int		is_builtin(const char *cmd);
int		ft_echo(t_token *cmd);
int 	ft_cd(t_token *cmd, t_env *env);
void	ft_execute(t_token *cmd, t_env *env);

// ------------------------------------------------------------ //
// -------------------- executions functions ------------------ //

#endif