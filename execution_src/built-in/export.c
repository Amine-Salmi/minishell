#include "../../includes/minishell.h"

void    print_env_var(t_env *env)
{
    while (env)
    {
        if (!env->content)
            return ;
        printf("declare -x %s=", env->content->var);
        printf("%s\n", env->content->value);
        env = env->next;
    }
}

int check_elements(char *elemnt)
{
    int i;
    
    if (elemnt[0] != '_' || ft_isalpha(elemnt[0]))
        return (1);
    i = 1;
    while(elemnt[i])
    {
        if (ft_isalpha(elemnt[i]) || ft_isdigit(elemnt[i]) || elemnt[i] != '=')
            return (1);
        i++;
    }
    return 0;
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
        // if (check_elements(cmd->arg[i]) != 0)
        // {
        //     printf("mminishell-0.1: export: `%s': a not valid identifier\n", cmd->arg[i]);
        //     return (1);
        // }
        new_node = create_new_elemnts(cmd->arg[i], env);
        add_to_env(env, new_node);
        i++; 
    }
    return 0;
}
