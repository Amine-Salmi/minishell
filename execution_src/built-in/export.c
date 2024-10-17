#include "../../includes/minishell.h"

void    print_env_var(t_env *env)
{
    while (env)
    {
        if (!env->content)
            return ;
        printf("%s=", env->content->var);
        printf("%s\n", env->content->value);
        env = env->next;
    }
}

t_env *create_new_elemnts(char *args, t_env *env)
{
    t_env *new_node;
    char **elemnts;
    int i;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->content = malloc(sizeof(t_content));
    if (!new_node->content)
    {
        free(new_node);
        return (NULL);
    }
    elemnts = ft_split(args, '=');
    if (!elemnts)
    {
        free(new_node);
        free(new_node->content);
        return (NULL);
    }
    i = 0;
    new_node->content->var = elemnts[0];
    new_node->content->value = elemnts[1];
    return (new_node);
}
t_env *lstlast(t_env *last)
{
    while (last)
    {
        last = last->next;
    }
    return (last);
}

void add_to_env(t_env *env, t_env *new_node)
{
    t_env *last;

    if (!env)
    {
        env = new_node;
        return ;
    }
    last = lstlast(env);
    last->next = new_node;
}

int ft_export(t_token *cmd, t_env *env)
{
    int i;
    char **content;
    t_env *new_node;

    i = 1;
    if (cmd->arg[i] == NULL)
    {
        print_env_var(env);
        return (0);
    }
    while (cmd->arg[i])
    {
        new_node = create_new_elemnts(cmd->arg[i], env);
        add_to_env(env, new_node);
        i++;
    }
    return 0;
}
