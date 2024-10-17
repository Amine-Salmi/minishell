/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:56 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/16 23:57:38 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    handle_heredoc(t_token *cmd)
{
    int fd;
    char *input_line;
    const char  *heredoc_file;
    t_opr *redi;
    pid_t pid;
    int status;
    // t_redirection *node;

    heredoc_file = "/tmp/herdoc_file.txt";
    redi = cmd->file;
    pid = fork();
    if (pid == 0)
    {
        unlink(heredoc_file);
        fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // while (redi)
        // {
            while (1)
            {
                input_line = readline("> ");
                if (input_line == NULL)
                {
                    free(input_line);
                    exit(EXIT_FAILURE);
                }
                if (redi->del != NULL && ft_strncmp(input_line, redi->del, ft_strlen(redi->del)) == 0)
                {
                    free(input_line);
                    break;
                }
                ft_putendl_fd(input_line, fd);
                free(input_line);
            // }
            // redi = redi->next;
        }
    }
    else if (pid > 0)
    {
        close(fd);
        wait(NULL);
    }
    redi->file_name = ft_strdup(heredoc_file);
}
