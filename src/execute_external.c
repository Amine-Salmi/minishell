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

int *execute_external_command(char **args, char **env)
{
    t_env *my_env;
    pid_t pid;
    char *path;
    char *executable_path;
    int status;

    my_env = copy_env(env);
    path = find_path(my_env);
    executable_path = find_executable_file(args[0] ,path);
    pid = fork();
    if (pid == 0)
    {
        if (executable_path)
        {
            execve(executable_path, args, NULL);
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
