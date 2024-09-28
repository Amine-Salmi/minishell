#include "../includes/minishell.h"

char *find_executable_file(char *command, char *path)
{
    char *executable_path;
    char **dirs;
    int i;

    dirs = ft_split(path, ':');
    i = 0;
    while (dirs[i])
    {
        executable_path = ft_strjoin(ft_strjoin(dirs[i], "/"), command);
        if (access(executable_path, F_OK | X_OK) == 0)
            return (executable_path);
        free(executable_path);
        i++;
    }
    return (NULL);
}

int *execute_external_command(t_command *cmd, char **env)
{
    t_env *my_env;
    pid_t pid;
    char *path;
    char *executable_path;
    int status;

    my_env = copy_env(env);
    path = find_path(my_env);
    executable_path = find_executable_file(cmd->args[0] ,path);
    pid = fork();
    if (pid == 0)
    {
        if (executable_path)
        {
            execve(executable_path, cmd->args, NULL);
        }
        else
        {
            printf("command not found\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)
        waitpid(pid, &status, 0);
    return (0);
}

void execute_piped_commands(t_command *cmd, char **env)
{
    // printf("is a pipe\n");
    int fd[2];
    int prev_fd;
    int pid;
    char *path;
    char *executable_path;
    int status;
    t_env *my_env;

    my_env = copy_env(env);
    prev_fd = -1;
    path = find_path(my_env);
    while (cmd)
    {

        executable_path = find_executable_file(cmd->args[0], path);
        if (cmd->next != NULL && cmd->next->type == PIPE)
        {
            pipe(fd);
        }
        pid = fork();
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmd->next != NULL && cmd->next->type == PIPE)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            if (executable_path == NULL)
            {
                printf("command not found\n");
                exit(EXIT_FAILURE);
            }
            execve(executable_path, cmd->args, NULL);
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);
            if (prev_fd != -1)
                close(prev_fd);
            if (cmd->next != NULL && cmd->next->type == PIPE)
            {
                close(fd[1]);
                prev_fd = fd[0];
            }
        }
        cmd = cmd->next; 
    }
}
