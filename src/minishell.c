/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:42 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/09 23:11:48 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_command *test_token(char *input_line)
// {
//     t_command *cmd;
//     char *token;
//     int i = 0;

//     cmd = malloc(sizeof(t_command));
//     cmd->args = malloc(sizeof(char *) * 100);
//     if (cmd == NULL || cmd->args == NULL)
//         exit(EXIT_FAILURE);
//     token = strtok(input_line, " ");
//     cmd->command = token;
//     cmd->type = CMD;
//     while (token != NULL)
//     {
//         if (strcmp(token, ">") == 0)
//         {
//             t_redirection *new_redirection = malloc(sizeof(t_redirection));
//             if (new_redirection == NULL)
//                 exit(EXIT_FAILURE);
//             token = strtok(NULL, " ");
//             new_redirection->file_name = token;
//             new_redirection->red_type = REDIR_OUT;
//             new_redirection->next = NULL;
//             if (cmd->redirection == NULL)
//                 cmd->redirection = new_redirection;
//             else {
//                 t_redirection *current = cmd->redirection;
//                 while (current->next != NULL)
//                     current = current->next;
//                 current->next = new_redirection;
//             }
//             token = strtok(NULL, " ");
//             continue;
//         }
//         if (strcmp(token, "<") == 0)
//         {
//             t_redirection *new_redirection = malloc(sizeof(t_redirection));
//             if (new_redirection == NULL)
//                 exit(EXIT_FAILURE);
//             token = strtok(NULL, " ");
//             new_redirection->file_name = token;
//             new_redirection->red_type = REDIR_IN;
//             new_redirection->next = NULL;
//             if (cmd->redirection == NULL)
//                 cmd->redirection = new_redirection;
//             else {
//                 t_redirection *current = cmd->redirection;
//                 while (current->next != NULL)
//                     current = current->next;
//                 current->next = new_redirection;
//             }
//             token = strtok(NULL, " ");
//             continue;
//         }
//         if (strcmp(token, "|") == 0)
//         {
//             cmd->args[i] = NULL;
//             cmd->next = malloc(sizeof(t_command));
//             if (cmd->next == NULL)
//                 exit(EXIT_FAILURE);
//             cmd->next->prev = cmd;
//             cmd->next->type = PIPE;
//             cmd->next->next = test_token(NULL);
//             return cmd;
//         }
//         cmd->args[i] = token;
//         i++;
//         token = strtok(NULL, " ");
//     }
//     cmd->args[i] = NULL;
//     cmd->next = NULL;
//     return cmd;
// }

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
    cmd->command = "cat";
    cmd->args = malloc(sizeof(char *) * 2);
    if (!cmd->args)
        exit(EXIT_FAILURE);
    cmd->args[0] = "cat";
    cmd->args[1] = NULL;
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
    redirection->file_name = NULL;
    redirection->opr = "<<";
    redirection->delimiter = "EOF";
    redirection->next = NULL;

    // redirection2 = malloc(sizeof(t_redirection));
    // if (!redirection2)
    //     exit(EXIT_FAILURE);
    // redirection2->file_name = NULL;
    // redirection2->red_type = HEREDOC;
    // redirection2->next = NULL;
    // redirection2->delimiter = "B";
    // redirection->next = redirection2;
    
    cmd->redirection = redirection;
    cmd->next = NULL;

    return (cmd);
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
        // printf("command: %s\n", cmd->command);
        // for (int i = 0; cmd->args[i]; i++)
        //     printf("args cmd[%d]: %s\n", i, cmd->args[i]);
        // printf("redirection: %s\n", cmd->redirection->file_name);
        // printf("redirection: %s\n", cmd->redirection->opr);
        // printf("command 2: %s\n", cmd->next->command);
        // for (int j = 0; cmd->next->args[j]; j++)
        //     printf("args cmd 2: %s\n", cmd->next->args[j]);
        execute_piped_commands(cmd, env);
        free(input_line);
    }
    return EXIT_SUCCESS;
}
