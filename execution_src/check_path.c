#include "../includes/minishell.h"

int file_ok(char *exec_path, t_token *cmd, t_env *env)
{
    struct stat stat_buf;

    if (access(exec_path, F_OK) == -1)
    {
        print_error("No such file or directory\n", cmd->command);
        env->exit_status = 127;
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
        env->exit_status = 126;
        return (-1);
    }
    if (access(exec_path, X_OK) == -1)
    {
        print_error("Permission denied\n", cmd->command);
        env->exit_status = 126;
        return (-1);
    }
    return (0);
}

void free_split(char **dirs)
{
    int i;

    i = 0;
    while (dirs[i])
    {
        free(dirs[i]);
        i++;
    }
    free(dirs);
}

// free memory in this function ---------------------
char *find_executable_file(t_token *cmd, t_env *env, char *path)
{
    char *executable_path;
    char *tmp_path;
    char **dirs;
    int i;
    int flg;

    dirs = ft_split(path, ':');
    free(path);
    i = 0;
    flg = 0;
    while (dirs[i])
    {
        tmp_path = ft_strjoin(dirs[i], "/");
        executable_path = ft_strjoin(tmp_path, cmd->command);
        free(tmp_path);
        if (access(executable_path, F_OK) == 0 && cmd->command[0] != '\0')
        {
            if (access(executable_path, X_OK) == 0)
            {
                free_split(dirs);
                return (executable_path);
            }
            print_error("Permission denied\n", executable_path);
            free(executable_path);
            flg = 1;
            env->exit_status = 126;
            break ;
        }
        free(executable_path);
        i++;
    }
    free_split(dirs);
    if (!flg)
    {
        print_error("command not found\n", cmd->command);
        env->exit_status = 127;
    }
    return (NULL);
}

char *check_path(t_token *cmd, t_env *env)
{
    char *path;
    char *tmp_path;
    char cwd_buff[PATH_MAX];

    if (ft_strchr(cmd->command, '/'))
    {
        if (!file_ok(cmd->command, cmd, env))
            return (cmd->command);
        return NULL;
    }
    path = find_var_env(env, "PATH");
    if (!path)
    {
        if (!getcwd(cwd_buff, sizeof(cwd_buff)))
        {
            perror("getcwd");
            return (NULL);
        }
        tmp_path = ft_strjoin(cwd_buff, "/");
        path = ft_strjoin(tmp_path, cmd->command);
        free(tmp_path);
        if (!file_ok(path, cmd, env))
            return (path);
        free(path);
        return (NULL);
    }
    return (find_executable_file(cmd, env, path));
}
