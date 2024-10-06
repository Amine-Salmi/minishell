#include "../includes/minishell.h"

void    handle_heredoc(t_command *cmd)
{
    int fd;
    char *input_line;
    char *file_path;
    const char *home_dir;

    fd = open("/tmp/herdoc_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        input_line = readline("> ");
        if (input_line == NULL)
        {
            free(input_line);
            exit(EXIT_FAILURE);
        }
        if (!ft_strncmp(input_line, cmd->redirection->delimiter, ft_strlen(cmd->redirection->delimiter)))
            break;
        if (cmd->redirection->next == NULL)
        {
            // printf("in this\n")
            write(fd, input_line, ft_strlen(input_line));
            write(fd, "\n", 1);
        }
        free(input_line);
    }
    close(fd);
    if (cmd->redirection->next == NULL)
    {
        fd = open("/tmp/herdoc_file.txt", O_RDONLY);
        if (fd < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    unlink("/tmp/herdoc_file.txt");
}
