#include <stdio.h>
#include <stdlib.h>

typedef struct s_token {
    int value; // Example field; adjust as needed
} t_token;

typedef struct s_lst {
    t_token *token;
    struct s_lst *next;
} t_lst;

// Create a new list node
t_lst *ft_lst_new(t_token *content) {
    t_lst *node = malloc(sizeof(t_lst));
    if (!node) return NULL;
    node->token = content;
    node->next = NULL;
    return node;
}

// Add a new node at the end of the list
void ft_lst_add_back(t_lst **lst, t_token *content) {
    t_lst *new = ft_lst_new(content);
    if (!new) return; // Handle memory allocation failure
    if (*lst == NULL) {
        *lst = new;
    } else {
        t_lst *last = *lst;
        while (last->next) {
            last = last->next;
        }
        last->next = new;
    }
}

// Free the entire list
void ft_lst_clear(t_lst **lst) {
    t_lst *current = *lst;
    t_lst *next;
    while (current) {
        next = current->next;
        free(current->token); // Free token if it was dynamically allocated
        free(current);
        current = next;
    }
    *lst = NULL;
}

// Function to print the list (for testing)
void ft_lst_print(t_lst *lst) {
    while (lst) {
        if (lst->token) {
            printf("%d -> ", lst->token->value);
        }
        lst = lst->next;
    }
    printf("NULL\n");
}

// Main function to test the linked list implementation
int main() {
    t_lst *list = NULL; // Initialize the list as empty

    // Add some tokens to the list
    for (int i = 0; i < 5; i++) {
        t_token *new_token = malloc(sizeof(t_token));
        if (!new_token) {
            perror("Failed to allocate memory for token");
            return 1;
        }
        new_token->value = i; // Assign some values
        ft_lst_add_back(&list, new_token);
    }

    // Print the list
    printf("List contents: ");
    ft_lst_print(list);

    // Clear the list and free memory
    ft_lst_clear(&list);

    return 0;
}
