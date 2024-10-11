#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "../lib/Libft/libft.h"
#include <fcntl.h>

typedef enum s_type {
    CMD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
} t_type;

typedef struct s_env {
    char **var;
    char **value;
}           t_env;

typedef struct s_redirection {
    char *file_name;
    int fd;
    // t_type red_type;
    char *opr;
    char *delimiter;
    struct s_redirection *next;
} t_redirection;

typedef struct s_command
{
    char *command;
    char **args;
    pid_t pid;
    // t_type type;
    t_redirection *redirection;
    struct s_command *next;
    struct s_command *prev;  
}              t_command;

t_env   *copy_env(char **env);
char    *find_path(t_env *env);
// int *execute_external_command(t_command *cmd, char **env);
void    execute_piped_commands(t_command *cmd, char **env);
void    redirection_handler(t_command *cmd);
void    handle_heredoc(t_command *cmd);
// void ft_execute(t_command *cmd, char **env);

#endif