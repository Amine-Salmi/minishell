/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/13 18:21:14 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"
#include "../includes/minishell_merg.h"

int execute_simple_command(t_token *cmd, char **env)
{
    pid_t pid;
    int status;
    char *path;
    char *executable_path;
    t_env *my_env;

    // my_env = copy_env(env);
    my_env = get_env(env);
    pid = fork();
    if (pid == 0)
    {
        // if (cmd->redirection)
        //     redirection_handler(cmd);
        path = find_path(my_env);
        printf("path : %s\n", path);
        executable_path = find_executable_file(cmd->command, path);
        if (execve(executable_path, cmd->arg, NULL) == -1)
        {
            perror("execve");
            return 1;
        }
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
    else
        return 1;
    return 0;
}

void ft_execute(t_token *cmd, char **env)
{
    printf("command: %s\n", cmd->command);
    for (int i = 0; cmd->arg[i] != NULL; i++)
        printf("args: %s\n", cmd->arg[i]);
    if (cmd->next == NULL)
    {
        if (execute_simple_command(cmd, env) != 0) // should free memory in find_executable_file and path.
            exit(EXIT_FAILURE);
    }
    // else if (cmd->next != NULL)
    // {
    //     execute_piped_commands(cmd, env); // // should free memory in find_executable_file and path.
    // }
}

// int main(int ac, char **av, char **env)
// {
//     t_command *cmd;
//     t_env *my_env;
//     pid_t pid;
//     char *input_line;
//     int status;

//     while (1)
//     {
//         input_line = readline("\033[1;31m-\033[0m  \033[1;32mminishell-0.1$\033[0m ");
//         if (input_line == NULL)
//         {
//             free(input_line);
//             exit(EXIT_FAILURE);
//         }
//         // cmd = fill_cmd();
//         ft_execute(cmd, env);
//         free(input_line);
//     }
//     return EXIT_SUCCESS;
// }
