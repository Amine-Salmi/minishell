#include "../includes/minishell.h"

void    handle_heredoc(t_command *cmd)
{
    int fd;
    char *input_line;
    const char *home_dir;
    t_redirection *redi = cmd->redirection;

    fd = open("/tmp/herdoc_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    while (redi)
    {
        while (1)
        {
            input_line = readline("> ");
            if (input_line == NULL)
            {
                free(input_line);
                exit(EXIT_FAILURE);
            }
            // printf(">>>>>>> before if d:%s\n", redi->delimiter);
            if (redi->delimiter != NULL && ft_strncmp(input_line, redi->delimiter, ft_strlen(redi->delimiter)) == 0)
            {
                // printf(">>>>> after if\n");
                free(input_line);
                break;
            }
            if (redi->next == NULL)
                ft_putendl_fd(input_line, fd);
            free(input_line);
        }
        redi = redi->next;
    }
    close(fd);
    fd = open("/tmp/herdoc_file.txt", O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}
