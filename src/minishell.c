/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/09/21 12:45:19 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command test_token(char *input_line)
{
    t_command cmd;
    char *token;
    int i = 0;

    cmd.args = malloc(sizeof(char *) * 10);
    if (cmd.args == NULL)
        exit(EXIT_FAILURE);
    token = strtok(input_line, " ");
    cmd.command = token;
    while (token != NULL)
    {
        cmd.args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    cmd.args[i] = NULL;
    return cmd;
}

t_env *copy_env(char **env)
{
    t_env *my_env;
    int i;
    char *equal_sign;

    i = 0;
    while (env[i])
        i++;
    my_env = malloc(sizeof(t_env));
    my_env->var = malloc(sizeof(char*) * (i + 1));
    my_env->value = malloc(sizeof(char*) * (i + 1));
    if (!my_env || !my_env->var || !my_env->value)
        return (NULL);
    i = 0;
    while (env[i])
    {
        equal_sign = ft_strchr(env[i], '=');
        if (equal_sign)
        {
            my_env->var[i] = ft_substr(env[i], 0, equal_sign - env[i]);
            my_env->value[i] = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
        }
        i++;
    }
    my_env->var[i] = NULL;
    my_env->value[i] = NULL;
    return (my_env);
}

int main(int ac, char **av, char **env)
{
    t_command cmd;
    t_env *my_env;
    pid_t pid;
    char *input_line;
    char *path;

    path = getenv("PATH");
    while (1)
    {
        input_line = readline("\033[1;31m-\033[0m  \033[1;32mminishell-0.1$\033[0m ");
        if (input_line == NULL)
        {
            free(input_line);
            exit(1);
        }
        cmd = test_token(input_line);
        my_env = copy_env(env);
        // pid = fork();
        // if (pid == 0)
        // {
        //     execve(path, cmd.args, env);
        //     exit(0);
        // }
        free(input_line);
    }
    return EXIT_SUCCESS;
}