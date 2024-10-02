#include "../includes/minishell.h"

void redirection_handler(t_command *cmd)
{
    int fd;

    if (cmd->outfile != NULL)
    {
        fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}