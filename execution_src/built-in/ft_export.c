#include "../../includes/minishell.h"

void    print_env_var(t_env *env)
{
    while (env)
    {
        if (!env->content)
            return ;
        printf("declare -x %s", env->content->var);
        if (env->content->value)
            printf("=\"%s\"\n", env->content->value);
        else
            printf("\n");
        env = env->next; 
    }
}

int check_export_elements(char *var)
{
    int i;

    if (!ft_isalpha(var[0]) && var[0] != '_')
        return (1);
    i = 1;
    while (var[i])
    {
        if (var[i] == '=')
            return (0);
        if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
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
        if (!ft_strcmp(var->content->var, env->content->var))
        {
            if (var->content->value)
                env->content->value = var->content->value;
            return (1);
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
    elemnts = split_first_eq(args, '=');
    if (!elemnts)
    {
        free(new_node);
        free(new_node->content);
        return (NULL);
    }
    new_node->content->var = ft_strdup(elemnts[0]);
    if (elemnts[1])
        new_node->content->value = ft_strdup(elemnts[1]);
    else
        new_node->content->value = NULL;
    free(elemnts[0]);
    if (elemnts[1])
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
        
        if (!check_export_elements(cmd->arg[i]))
        {
            new_node = create_new_elemnts(cmd->arg[i], env);\
            if (!elemnt_exist(new_node, env))    
                add_to_env(env, new_node);
        }
        else
        {
            printf("mminishell-0.1: export: `%s': a not valid identifier\n", cmd->arg[i]);
            return (1);
        }
        i++; 
    }
    return 0;
}
