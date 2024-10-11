#include "../includes/minishell.h"

void    handle_heredoc(t_command *cmd)
{
    int fd;
    char *input_line;
    const char  *heredoc_file;
    t_redirection *redi = cmd->redirection;
    pid_t pid;
    int status;
    t_redirection *node;

    heredoc_file = "/tmp/herdoc_file.txt";
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
        while (cmd->redirection)
        {
            while (1)
            {
                input_line = readline("> ");
                if (input_line == NULL)
                {
                    free(input_line);
                    exit(EXIT_FAILURE);
                }
                if (cmd->redirection->delimiter != NULL && ft_strncmp(input_line, cmd->redirection->delimiter, ft_strlen(cmd->redirection->delimiter)) == 0)
                {
                    free(input_line);
                    break;
                }
                ft_putendl_fd(input_line, fd);
                free(input_line);
                // node = cmd->redirection;
            }
            cmd->redirection = cmd->redirection->next;
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        close(fd);
    }
    cmd->redirection->file_name = ft_strdup(heredoc_file);
}
