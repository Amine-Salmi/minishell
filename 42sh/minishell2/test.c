#include "stdio.h"
#include "stdlib.h"

typedef struct s_l
{
	char			*content;
	int 			id;
}t_l;
typedef struct s_list
{
	t_l			content;
	struct s_list	*next;
	struct s_list	*prev;
}t_list;


t_list	*creat_list(t_l *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if(!node)
		return (NULL);
	if (node)
	{
		node->content = *content;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	add_list_back(t_list **lst, t_l *content)
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

int main (int ac, char *av[])
{
	t_list *node1;
	t_l content;
	t_l content2;
	t_l content3;
	content.content = av[1];
	content.id = 0;
	content2.content = av[2];
	content2.id = 1;
	content3.content = av[3];
	content3.id = 2;

	node1 = creat_list(&content);
    add_list_back(&node1, &content2);
    add_list_back(&node1, &content3);
    t_list *tmp;
    tmp = node1;
    while(tmp)
    {
        printf("content :%s\n", tmp->content.content);
        printf("id :%d\n", tmp->content.id);
        if (tmp->prev)
            printf("his prv : %s\n", tmp->prev->content.content);
        tmp = tmp->next;
    }
}