#include "../includes/minishell.h"

int file_ok(char *exec_path, t_token *cmd)
{
    struct stat stat_buf;

    if (access(exec_path, F_OK) == -1)
    {
        print_error("No such file or directory\n", cmd->command);
        return (-1);
    }
    if (stat(exec_path, &stat_buf) == -1)
    {
        perror("stat: ");
        return (-1);
    }
    if (S_IFDIR == (S_IFMT & stat_buf.st_mode))
    {
        print_error("is a directory\n", cmd->command);
        return (-1);
    }
    if (access(exec_path, X_OK) == -1)
    {
        print_error("Permission denied\n", cmd->command);
        return (-1);
    }
    return (0);
}

// free memory in this function ---------------------
char *find_executable_file(char *command, char *path)
{
    char *executable_path;
    char **dirs;
    int i;
    int flg ;

    dirs = ft_split(path, ':');
    i = 0;
    flg = 0;
    while (dirs[i])
    {
        executable_path = ft_strjoin(ft_strjoin(dirs[i], "/"), command);
        if (access(executable_path, F_OK) == 0)
        {
            if (access(executable_path, X_OK) == 0)
                return (executable_path);
            print_error("Permission denied\n", executable_path);
            flg = 1;
            break ;
        }
        free(executable_path);
        i++;
    }
	i = 0;
    if (!flg)
        print_error("command not found\n", command);
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
    }
    return (find_executable_file(cmd->command, path));
}
