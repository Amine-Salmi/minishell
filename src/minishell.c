/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/09/22 18:06:28 by asalmi           ###   ########.fr       */
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

char *find_exec(char **dirs, char *command)
{
    char *path;
    int i;

    i = 0;
    while (dirs[i])
    {
        path = ft_strjoin(ft_strjoin(dirs[i], "/"), command);
        if (access(path, F_OK | X_OK) == 0)
            return path;
        free(path);
        i++;
    }
    return NULL;
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
        my_env = copy_env(env);
        // for (int i = 0; my_env->var[i]; i++)
        //     printf("%s=%s\n", my_env->var[i], my_env->value[i]);
        find_path(my_env);
        char **dirs = ft_split(my_env->path, ':');
        char *executable_path = find_exec(dirs, cmd.command);
        pid = fork();
        if (pid == 0)
        {
            if (executable_path)
            {
                execve(executable_path, cmd.args, NULL);
            }
            else
                printf("command not Found\n");
            exit(0);
        }
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
        }
        free(input_line);
    }
    return EXIT_SUCCESS;
}