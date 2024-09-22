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
#include "../lib/Libft/libft.h"

typedef struct s_env {
    char **var;
    char **value;
    char *path;
}           t_env;

typedef struct s_command
{
    char *command;
    char **args;
    struct s_command *next;
}              t_command;

t_env *copy_env(char **env);
void    find_path(t_env *env);

#endif