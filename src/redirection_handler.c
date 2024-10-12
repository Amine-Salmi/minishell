#include "../includes/minishell.h"

void redirection_handler(t_command *cmd)
{
    int fd;
    int i;

    i = 0;
    while (i < 2)
    {
        if (!ft_strncmp(cmd->redirection[i].opr, ">", ft_strlen(cmd->redirection[i].opr)))
        {
            fd = open(cmd->redirection[i].file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            if (cmd->redirection[i].file_name == NULL)
                dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (!ft_strncmp(cmd->redirection[i].opr, "<<", ft_strlen(cmd->redirection[i].opr)))
        {
            fd = open(cmd->redirection[i].file_name, O_RDONLY);
            if (fd < 0)
            {
                perror("open test");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (!ft_strncmp(cmd->redirection[i].opr, "<", ft_strlen(cmd->redirection[i].opr)))
        {
            fd = open(cmd->redirection[i].file_name, O_RDONLY);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            if (cmd->redirection[i].next == NULL)
                dup2(fd, STDIN_FILENO);
            close(fd);
        }
       
        if (!ft_strncmp(cmd->redirection[i].opr, ">>", ft_strlen(cmd->redirection[i].opr)))
        {
            fd = open(cmd->redirection[i].file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            if (cmd->redirection[i].next == NULL)
                dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        i++;
    }
}
