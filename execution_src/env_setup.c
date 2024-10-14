#include "../includes/minishell_merg.h"

size_t count_node(t_env *env)
{
    t_env *tmp;
    size_t count;

    tmp = env;
    count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}
char **copy_env(t_env *env)
{
    char **env_copy;
    size_t size;
    int i;
    int j;

    size = count_node(env);
    env_copy = malloc(sizeof(char *) * (size + 1));
    if (!env_copy)
        return (NULL);
    i = 0;
    j = 0;
    while (env)
    {
        env_copy[i] = ft_strdup(env->content->var);
        env_copy[i] = ft_strjoin(env_copy[i], "=");
        env_copy[i] = ft_strjoin(env_copy[i], env->content->value);
        if (!env_copy[i])
            return (NULL);
        env = env->next;
        i++;
    }
    env_copy[i] = NULL;
    return (env_copy);
}
// t_env *copy_env(char **env)
// {
//     t_env *my_env;
//     int i;
//     char *equal_sign;

//     i = 0;
//     while (env[i])
//         i++;
//     my_env = malloc(sizeof(t_env));
//     my_env->var = malloc(sizeof(char*) * (i + 1));
//     my_env->value = malloc(sizeof(char*) * (i + 1));
//     if (!my_env || !my_env->var || !my_env->value)
//         return (NULL);
//     i = 0;
//     while (env[i])
//     {
//         equal_sign = ft_strchr(env[i], '=');
//         if (equal_sign)
//         {
//             my_env->var[i] = ft_substr(env[i], 0, equal_sign - env[i]);
//             my_env->value[i] = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
//         }
//         i++;
//     }
//     my_env->var[i] = NULL;
//     my_env->value[i] = NULL;
//     return (my_env);
// }

// free memory in this function ----------------

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

// free memory in this function ----------------

char     *find_path(t_env *env)
{
    int i;
    char *path;

    i = 0;
    while (env)
    {
        if (!ft_strncmp(env->content[i].var, "PATH", ft_strlen("PATH")))
        {
            path = ft_substr(env->content[i].value, 0, ft_strlen(env->content[i].value));
            return (path);
        }
        env = env->next;
    }
    return (NULL);
}
