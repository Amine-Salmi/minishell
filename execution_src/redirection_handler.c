#include "../includes/minishell_merg.h"

void redirection_handler(t_token *cmd)
{
    int fd;
    int i;

    i = 0;
    while (cmd->file)
    {
        printf("file name: %s\n", cmd->file[i].file_name);
        printf("operatore: %s\n", cmd->file[i].opr);
        i++;
    }
    // while (cmd->redirection)
    // {
    //     if (!ft_strncmp(cmd->redirection->opr, ">", ft_strlen(cmd->redirection->opr)))
    //     {
    //         fd = open(cmd->redirection->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    //         if (fd < 0)
    //         {
    //             perror("open");
    //             exit(EXIT_FAILURE);
    //         }
    //         if (cmd->redirection->next == NULL)
    //             dup2(fd, STDOUT_FILENO);
    //         close(fd);
    //     }
    //     if (!ft_strncmp(cmd->redirection->opr, "<<", ft_strlen(cmd->redirection->opr)))
    //     {
    //         fd = open(cmd->redirection->file_name, O_RDONLY);
    //         if (fd < 0)
    //         {
    //             perror("open test");
    //             exit(EXIT_FAILURE);
    //         }
    //         dup2(fd, STDIN_FILENO);
    //         close(fd);
    //     }
    //     if (!ft_strncmp(cmd->redirection->opr, "<", ft_strlen(cmd->redirection->opr)))
    //     {
    //         fd = open(cmd->redirection->file_name, O_RDONLY);
    //         if (fd < 0)
    //         {
    //             perror("open");
    //             exit(EXIT_FAILURE);
    //         }
    //         if (cmd->redirection->next == NULL)
    //             dup2(fd, STDIN_FILENO);
    //         close(fd);
    //     }
       
    //     if (!ft_strncmp(cmd->redirection->opr, ">>", ft_strlen(cmd->redirection->opr)))
    //     {
    //         fd = open(cmd->redirection->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
    //         if (fd < 0)
    //         {
    //             perror("open");
    //             exit(EXIT_FAILURE);
    //         }
    //         if (cmd->redirection->next == NULL)
    //             dup2(fd, STDOUT_FILENO);
    //         close(fd);
    //     }
    //     cmd->redirection = cmd->redirection->next;
    // }
}
