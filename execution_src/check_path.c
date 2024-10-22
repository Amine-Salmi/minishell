#include "../includes/minishell.h"

int file_ok(char *executable_path)
{
    struct stat file_stat;

	if (access(executable_path, F_OK))
    {
        printf("minishell: ls: No such file or directory\n");
        return (1);
    }
    if (access(executable_path, X_OK))
    {
        printf("minishell: ls: Permission denied\n");
        return (1);
    }
    if (stat(executable_path, &file_stat))
    {
        perror("stat:");
        return (1);
    }
    if (S_IFDIR == (file_stat.st_mode))
    {
        printf("minishell: ls: Is a directory\n");
        return (1);
    }
	return 0;
}

// free memory in this function ---------------------
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
	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
    return (NULL);
}

char *check_path(t_token *cmd, t_env *env)
{
    char *path;
    char cwd_buffer[PATH_MAX];

    if (ft_strchr(cmd->command, '/'))
    {
        if (!file_ok(cmd->command))
            return (cmd->command);
    }
    path = find_var_env(env, "PATH");
    if (!path)
    {
        if (!getcwd(cwd_buffer, sizeof(cwd_buffer)))
        {
            perror("getcwd:");
            return (NULL);
        }
        path = ft_strjoin(ft_strjoin(cwd_buffer, "/"), cmd->command);
        if (!file_ok(path))
            return (path);
    }
    return (find_executable_file(cmd->command, path)); 
}
