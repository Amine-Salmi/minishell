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

// typedef enum s_type_cmd {
//     cmd_nomral,
//     cmd_pipe,
// } t_type_cmd;

typedef struct s_env {
    char **var;
    char **value;
}           t_env;

typedef struct s_command
{
    char *command;
    char **args;
    bool has_pipe;
    struct s_command *next;
    struct s_command *prev;  
}              t_command;

t_env *copy_env(char **env);
char    *find_path(t_env *env);
int *execute_external_command(t_command *cmd, char **env);
void execute_piped_commands(t_command *cmd, char **env);

#endif