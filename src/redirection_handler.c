#include "../includes/minishell.h"

void redirection_handler(t_command *cmd)
{
    int fd;
    while (cmd->redirection)
    {
        if(cmd->redirection->red_type == REDIR_OUT)
        {
            fd = open(cmd->redirection->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            printf("im here\n");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        cmd->redirection = cmd->redirection->next;
    }
}