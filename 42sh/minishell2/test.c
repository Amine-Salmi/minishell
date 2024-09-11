#include "stdio.h"
#include "stdlib.h"

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	struct s_list	*prev;
}t_list;

t_list	*creat_list(char *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if(!node)
		return (NULL);
	if (node)
	{
		node->content = content;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	add_list_back(t_list **lst, char *content)
{
	t_list	*tmp;
	t_list	*new;

	new = creat_list(content);
	if (new && lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = *lst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
		}
	}
}
int main ()
{
	t_list *node1;
	t_list *node2;

	node1 = creat_list("bilal");
    add_list_back(&node1, "badda");
    add_list_back(&node1, "1337");
    t_list *tmp;
    tmp = node1;
    while(tmp)
    {
        printf("content :%s\n", tmp->content);
        if (tmp->prev)
            printf("his prv : %s\n", tmp->prev->content);
        tmp = tmp->next;
    }
}