#include "../includes/minishell.h"

t_env *copy_env(char **env)
{
    t_env *my_env;
    int i;
    char *equal_sign;

    i = 0;
    while (env[i])
        i++;
    my_env = malloc(sizeof(t_env));
    my_env->var = malloc(sizeof(char*) * (i + 1));
    my_env->value = malloc(sizeof(char*) * (i + 1));
    if (!my_env || !my_env->var || !my_env->value)
        return (NULL);
    i = 0;
    while (env[i])
    {
        equal_sign = ft_strchr(env[i], '=');
        if (equal_sign)
        {
            my_env->var[i] = ft_substr(env[i], 0, equal_sign - env[i]);
            my_env->value[i] = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
        }
        i++;
    }
    my_env->var[i] = NULL;
    my_env->value[i] = NULL;
    return (my_env);
}

void search_dir(char *path)
{
    char **res = ft_split(path, ':');
    for (int i = 0; res[i] != NULL; i++)
        printf("%s\n", res[i]);
}

void    check_path(t_env *env)
{
    int i;
    char *equel_sing;

    i = 0;
    while (env->var[i])
    {
        if (!ft_strncmp(env->var[i], "PATH", ft_strlen("PATH")))
        {
            env->path = ft_substr(env->value[i], 0, ft_strlen(env->value[i]));
            break;
        }
        i++;
    }
    search_dir(env->path);
}
