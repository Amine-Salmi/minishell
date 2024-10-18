#include "../../includes/minishell.h"

void    print_env_var(t_env *env)
{
    while (env)
    {
        if (!env->content)
            return ;
        printf("declare -x %s=", env->content->var);
        printf("\"%s\"\n", env->content->value);
        env = env->next;
    }
}

int check_elements(t_env *new_var)
{
    int i;

    if (!ft_isalpha(new_var->content->var[0]) && new_var->content->var[0] != '_')
    {
        return (1);
    }
    i = 1;
    while (new_var->content->var[i])
    {
        if (!ft_isdigit(new_var->content->var[i]) && !ft_isalpha(new_var->content->var[i]) && new_var->content->var[i] != '_')
            return (1);
        i++;
    }
    return (0);
}

int elemnt_exist(t_env *var, t_env *env)
{
    int i;
    char *value;

    i = 0;
    while (env)
    {
        if (!ft_strncmp(var->content->var, env->content->var, ft_strlen(var->content->var)))
        {
            env->content->value = var->content->value;
            return 1;
        }
        env = env->next;
    }
    return (0);
}

t_env *create_new_elemnts(char *args, t_env *env)
{
    t_env *new_node;
    char **elemnts;

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
    new_node->content->var = ft_strdup(elemnts[0]);
    new_node->content->value = ft_strdup(elemnts[1]);
    if (check_elements(new_node))
        return (NULL);
    // create function free double pointer
    free(elemnts[0]);
    free(elemnts[1]);
    free(elemnts);
    new_node->next = NULL;
    return (new_node);
}

t_env *lstlast(t_env *last)
{
    while (last && last->next != NULL)
        last = last->next;
    return (last);
}

void add_to_env(t_env *env, t_env *new_node)
{
    t_env *last;

    if (!env)
        env = new_node;
    else
    {
        last = lstlast(env);
        last->next = new_node;
    }
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
        if (!new_node)
        {
            printf("mminishell-0.1: export: `%s': a not valid identifier\n", cmd->arg[i]);
            return (1);
        }
        if (elemnt_exist(new_node, env))
            return 0;
        add_to_env(env, new_node);
        i++; 
    }
    return 0;
}
