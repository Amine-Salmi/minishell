/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/09/23 16:32:14 by asalmi           ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
    t_command cmd;
    t_env *my_env;
    pid_t pid;
    char *input_line;
    int status;

    while (1)
    {
        input_line = readline("\033[1;31m-\033[0m  \033[1;32mminishell-0.1$\033[0m ");
        if (input_line == NULL)
        {
            free(input_line);
            exit(1);
        }
        cmd = test_token(input_line);
        execute_external_command(cmd.args, env);
        free(input_line);
    }
    return EXIT_SUCCESS;
}