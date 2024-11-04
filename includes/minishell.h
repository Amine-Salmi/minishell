/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:11 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/04 12:14:15 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
// #include "readline/history.h"
// #include "readline/readline.h"
#include "/Users/bbadda/goinfre/homebrew/opt/readline/include/readline/history.h"
#include "/Users/bbadda/goinfre/homebrew/opt/readline/include/readline/readline.h"
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
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
	SPACEE = 3,
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
	char	*opr;
	char	*file_name;
	struct s_opr *next;
}t_opr;

typedef struct s_herdoc
{
	char	*herdoc;
	char	*del;
	bool	expend;
	t_opr	file;
	struct s_herdoc *next;
}t_herdoc;

typedef struct s_token
{
	char				*command;
	char				**arg;
	t_opr				*file;
	t_herdoc			*herdoc;
	pid_t				pid;
}t_token;

typedef struct s_lst
{
	t_token				*token;
	struct s_lst		*next;
	struct s_lst		*prev;
}t_lst;

typedef struct s_minishell
{
	char	**cmd;
	t_opr	opr;
}t_minishell;

typedef struct s_content 
{
	char *var;
	char *value;
}t_content;

typedef struct s_env 
{
	t_content 		*content;
	int 			exit_status;
	struct s_env 	*next;
}t_env;

typedef struct s_split
{
	char	**list;
	char		c;
}t_split;



int			cmp(const char *s1, const char *s2);
char		*get_pipe(char *line);
t_herdoc	*creatlist_herdoc(char *herdoc, char *del);
void		__add_back_file(t_opr **token, char *file_name, char *opr);
void		__add_back_herdoc(t_herdoc **token, char *herdoc, char *del);
void		__ft_lstadd_back(t_lst **lst, t_token *content);
void	    __error(char c, int i);
void		*__calloc(size_t count, size_t size);
// --------------------tokenization_functions-----------------//
void		__token (t_token *token, char **s_command, t_env *e);
t_index		max_files_args(char **s_command);
int			get_env_size(char *cmd, t_env *e);
char		*replace_env(t_env *e, char *s);
int			check_env(char *cmd);
char		*check_and_replace_env(char *s_command, t_env *e);
char		*remove_q(char *s_command);
void		quotes_status(char *cmd, int *i, bool *in_single_quotes, bool *in_quotes);
int			__lstsize(t_env *lst);

// --------------------syntax_error_functions-----------------//
int			syntax_error(char *command);
int			qoutes_error(char *command);
int			check_all_thing(char *command, int *i, int *j);
int			redir_error_check(char *command, int *i, int *j);
int			check_end_of_command(int i, int j);
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
// -------------------free_utils-----------------------------------//
void		simple_free(char **command);
void 		free_lst(t_lst *lst);
void 		free_token(t_token *token);
void    	free_list(char **list);

void			priiint(t_lst *lst);

// -------------------- executions functions ------------------ //
// ------------------------------------------------------------ //

char    *find_var_env(t_env *env, char *var);
char    *find_executable_file(t_token *command, t_env *env, char *path);
char	*check_path(t_token *cmd, t_env *env);
char	**copy_env(t_env *env);
void	add_to_env(t_env **env, t_env *new_node);
int    	redirection_handler(t_token *cmd, t_env *env);
void    handle_heredoc(t_lst *cmd);

void	execute_builtin(t_token *cmd, t_env **env);
int		is_builtin(const char *cmd);
int		ft_echo(t_token *cmd);
int 	ft_cd(t_token *cmd, t_env *env);
int 	ft_pwd(t_token *cmd);
int		ft_env(t_token *cmd, t_env *env);
int		ft_export(t_token *cmd, t_env **env);
int 	ft_unset(t_token *cmd, t_env **env);
int		update_pwd(t_env *env, char *old_pwd);

char	**split_first_eq(char const *s, char c);
void	ft_execute(t_lst *cmd, t_env **env);
void	execute_piped_commands(t_lst *cmd, t_env **env);

void	handler_signal(int mode);

void	free_double_pointer(char **env);
void	print_error(char *error_mesage, char *command);

// ------------------------------------------------------------ //
// -------------------- executions functions ------------------ //

#endif