#include "../includes/minishell.h"

int file_ok(char *exec_path, t_token *cmd)
{
    struct stat stat_buf;

    if (access(exec_path, F_OK) == -1)
    {
        print_error("No such file or directory\n", cmd->command);
        cmd->exit_status = 127;
        return (-1);
    }
    if (stat(exec_path, &stat_buf) == -1)
    {
        perror("stat:");
        return (-1);
    }
    if (S_IFDIR == (S_IFMT & stat_buf.st_mode))
    {
        print_error("is a directory\n", cmd->command);
        cmd->exit_status = 126;
        return (-1);
    }
    if (access(exec_path, X_OK) == -1)
    {
        print_error("Permission denied\n", cmd->command);
        cmd->exit_status = 126;
        return (-1);
    }
    return (0);
}

// free memory in this function ---------------------
char *find_executable_file(t_token *cmd, char *path)
{
    char *executable_path;
    char **dirs;
    int i;
    int flg;

    dirs = ft_split(path, ':');
    i = 0;
    flg = 0;
    while (dirs[i])
    {
        executable_path = ft_strjoin(ft_strjoin(dirs[i], "/"), cmd->command);
        if (access(executable_path, F_OK) == 0)
        {
            if (access(executable_path, X_OK) == 0)
                return (executable_path);
            print_error("Permission denied\n", executable_path);
            flg = 1;
            cmd->exit_status = 126;
            break ;
        }
        free(executable_path);
        i++;
    }
    if (!flg)
    {
        print_error("command not found\n", cmd->command);
        cmd->exit_status = 127;
    }
    free_double_pointer(dirs);
    return (NULL);
}

char *check_path(t_token *cmd, t_env *env)
{
    char *path;
    char cwd_buff[PATH_MAX];

    if (ft_strchr(cmd->command, '/'))
    {
        if (!file_ok(cmd->command, cmd))
            return (cmd->command);
        return NULL;
    }
    path = find_var_env(env, "PATH");
    if (!path)
    {
        if (!getcwd(cwd_buff, sizeof(cwd_buff)))
        {
            perror("getcwd:");
            return (NULL);
        }
        path = ft_strjoin(ft_strjoin(cwd_buff, "/"), cmd->command);
        if (!file_ok(path, cmd))
            return (path);
        return (NULL);
    }
    return (find_executable_file(cmd, path));
}
