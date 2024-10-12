/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/12 19:05:37 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command *fill_cmd(void)
{
    t_command *cmd;
    t_command *cmd2;
    // t_command *cmd3;
    t_redirection *redirection;
    // t_redirection *redirection2;
    
    cmd = malloc(sizeof(t_command));
    cmd2 = malloc(sizeof(t_command));
    // cmd3 = malloc(sizeof(t_command));
    if (!cmd || !cmd2)
        exit(EXIT_FAILURE);
    cmd->command = "ls";
    cmd->args = malloc(sizeof(char *) * 2);
    if (!cmd->args)
        exit(EXIT_FAILURE);
    cmd->args[0] = "ls";
    cmd->args[1] = NULL;
    cmd->next = NULL;
    // cmd->args[2] = NULL;
    // cmd->type = CMD;

    // cmd3->command = "wc";
    // cmd3->args = malloc(sizeof(char *) * 2);
    // if (!cmd3->args)
    //     exit(EXIT_FAILURE);
    // cmd3->args[0] = "wc";
    // cmd3->args[1] = NULL;
    // cmd3->type = CMD;
    // cmd3->next = NULL;
    
    cmd2->command = "wc";
    cmd2->args = malloc(sizeof(char *) * 3);
    if (!cmd2->args)
        exit(EXIT_FAILURE);
    cmd2->args[0] = "wc";
    cmd2->args[1] = "-l";
    cmd2->args[2] = NULL;
    // cmd2->type = PIPE;
    cmd2->next = NULL;

    
    redirection = malloc(sizeof(t_redirection));
    if (!redirection)
        exit(EXIT_FAILURE);
    redirection->file_name = "file";
    redirection->opr = ">";
    redirection->delimiter = NULL;
    redirection->next = NULL;

    // redirection2 = malloc(sizeof(t_redirection));
    // if (!redirection2)
    //     exit(EXIT_FAILURE);
    // redirection2->file_name = NULL;
    // redirection2->opr = "<<";
    // redirection2->delimiter = "B";
    // redirection2->next = NULL;
    
    redirection->next = NULL;
    
    cmd->redirection = NULL;
    cmd->next = cmd2;

    return (cmd);
}

int execute_simple_command(t_command *cmd, char **env)
{
    pid_t pid;
    int status;
    char *path;
    char *executable_path;
    t_env *my_env;

    my_env = copy_env(env);
    pid = fork();
    if (pid == 0)
    {
        // if (cmd->redirection)
        //     redirection_handler(cmd);
        path = find_path(my_env);
        executable_path = find_executable_file(cmd->command, path);
        if (execve(executable_path, cmd->args, NULL) == -1)
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

void ft_execute(t_command *cmd, char **env)
{
    if (cmd->next == NULL)
    {
        if (execute_simple_command(cmd, env) != 0)
            exit(EXIT_FAILURE);
    }
    else if (cmd->next != NULL)
    {
        execute_piped_commands(cmd, env);
    }
        
}

int main(int ac, char **av, char **env)
{
    t_command *cmd;
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
            exit(EXIT_FAILURE);
        }
        cmd = fill_cmd();
        ft_execute(cmd, env);
        free(input_line);
    }
    return EXIT_SUCCESS;
}
