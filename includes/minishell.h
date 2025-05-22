/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:11 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/17 02:11:31 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/Libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# define ARGS_ERROR "number of arguments"

extern bool			g_signal;

typedef struct s_index
{
	int				i;
	int				j;
	int				k;
}					t_index;
enum				e_token_type
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
enum				e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};
typedef struct s_opr
{
	char			*opr;
	char			*file_name;
	struct s_opr	*next;
}					t_opr;
typedef struct s_herdoc
{
	char			*herdoc;
	char			*del;
	bool			expend;
	t_opr			file;
	struct s_herdoc	*next;
}					t_herdoc;
typedef struct s_token
{
	char			*command;
	char			**arg;
	t_opr			*file;
	t_herdoc		*herdoc;
	pid_t			pid;
}					t_token;
typedef struct s_lst
{
	t_token			*token;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;
typedef struct s_minishell
{
	char			**cmd;
	t_opr			opr;
}					t_minishell;
typedef struct s_content
{
	char			*var;
	char			*value;
}					t_content;
typedef struct s_env
{
	t_content		*content;
	int				exit_status;
	struct s_env	*next;
}					t_env;
typedef struct s_split
{
	char			**list;
	char			c;
}					t_split;
typedef struct s_buffer
{
	char			*buffer;
	char			*cmd;
	char			*str;
	char			**cmd2;
	bool			in_sq;
	bool			in_q;
}					t_buffer;
void				allocate_for_me(t_index index, t_token *token);
int					cmp(const char *s1, const char *s2);
void				__put_and_exit(t_env *my_env);
char				*get_pipe(char *line);
void				__add_back_file(t_opr **token, char *file_name, char *opr);
void				__add_back_herdoc(t_herdoc **token, char *herdoc, char *del,
						bool expend);
void				__ft_lstadd_back(t_lst **lst, t_token *content);
void				__error(char c, int i);
void				*__calloc(size_t count, size_t size);
// --------------------tokenization_functions-----------------//
void				__token(t_token *token, char **s_command, t_env *e);
t_index				max_files_args(char **s_command);
int					get_env_size(char *cmd, t_env *e);
char				*replace_env(t_env *e, char *s);
int					check_env(char *cmd);
char				*__env(char *s_command, t_env *e);
char				*__env_heredoc(char *cmd, t_env *e);
char				*remove_q(char *s_command);
void				quotes_status(char *cmd, int *i, bool *in_single_quotes,
						bool *in_quotes);
int					__lstsize(t_env *lst);
t_env				*init_and_get_env(char **av, int ac, char **env);
void				extract_var_name(char *cmd, int *i, char *var_name,
						bool *in_the_first);
bool				special_char(char c, int index);
// --------------------syntax_error_functions-----------------//
int					syntax_error(char *command, t_env *env);
int					qoutes_error(char *command);
int					check_all_thing(char *command, int *i, int *j);
int					redir_error_check(char *command, int *i, int *j);
int					check_end_of_command(int i, int j);
void				__free(t_list **lst);
// ---------------------get_env_function----------------------//
t_env				*get_env(char **env);
char				*__strchr(char *str, int c);
bool				check_if_pair(char *cmd, int *i, bool *pair);
void				handle_dollar_sign(t_buffer string, int *i, t_env *e,
						int *index);
// --------------------add_spaces----------------------------//
char				*add_spaces(char *cmd);
int					__is_redir(char c);
int					__is_herdoc(char *s);
int					pipe_error(char *command, int j);
// -------------------libft-----------------------------------//
int					parse_strlen(const char *str);
char				*parse_substr(char const *str, int start, int len);
char				**parse_split(char const *s, char c);

char				*parse_strtrim(char const *str, char const *set);
char				*parse_strdup(const char *src);
// -------------------free_utils-----------------------------------//
void				simple_free(char **command);
void				free_lst(t_lst **lst);
void				free_token(t_token *token);
void				free_list(char **list);
void				free_env(t_env **env);
void				free_opr(t_opr *opr);
void				__add_list_special_case(t_env **lst, t_content *content);
// -------------------- executions functions ------------------ //
char				*check_path(t_token *cmd, t_env *env);
int					check_directory(t_token *cmd, char *exec_path, t_env *env);
int					file_ok(char *exec_path, t_token *cmd, t_env *env);
char				*construct_executable_path(char *dir, char *command);

char				*find_var_env(t_env *env, char *var);
char				*find_executable_file(t_token *command, t_env *env,
						char *path);
char				**copy_env(t_env *env);
void				add_to_env(t_env **env, t_env *new_node);

int					redirection_handler(t_token *cmd, t_env *env);
void				handle_heredoc(t_lst *cmd, t_env *env, char *heredoc_file);
void				parent_process_logic(pid_t pid, t_env *env);
void				free_file_list(t_opr *file);
char				*rename_file(char *str);
void				remove_file(void);

void				execute_builtin(t_token *cmd, t_env **env);
int					is_builtin(const char *cmd);
int					ft_echo(t_token *cmd);
int					ft_cd(t_token *cmd, t_env *env);
int					ft_pwd(void);
int					ft_env(t_token *cmd, t_env *env);
int					ft_export(t_token *cmd, t_env **env);
int					ft_unset(t_token *cmd, t_env **env);
int					ft_exit(t_token *cmd, t_env *env);
int					exit_with_status(t_token *cmd, t_env *env);
void				check_numeric_arg(t_token *cmd, t_env *env);
int					update_pwd(t_env *env, char *old_pwd);
char				*get_cd_path(t_token *cmd, t_env *env);
void				print_identifier_error(char *command, char *identifier);
char				**split_first_eq(char const *s, char c);
void				ft_execute(t_lst *cmd, t_env **env);
void				__check_and_execute(t_token *cmd, t_env **env);
void				restore_streams(int saved_out, int saved_in);
int					save_and_readirect(t_token *cmd, t_env **env,
						int *saved_out, int *saved_in);
int					is_valid_n(const char *arg);
void				free_env_content(t_env *node);
void				print_env_var(t_env *env);
t_env				*create_new_elemnts(char *args);
void				add_to_env(t_env **env, t_env *new_node);
void				assign_env_content(t_env *new_node, char **elemnt);
t_env				*lstlast(t_env *last);
void				execute_piped_commands(t_lst *cmd, t_env **env);
void				handle_fork_error(int *fd, int pipeline, t_env **env);
void				wait_last_child(t_env **env, pid_t last_pid);
t_env				*allocate_new_node(void);

void				handler_signal(int mode);
void				print_error(char *error_mesage, char *command);
void				free_double_p(char **dirs);
void				setup_signals(void);

void				rl_replace_line(const char *line, int mode);
void				priiint(t_lst *lst);
// -------------------- executions functions ------------------ //
#endif