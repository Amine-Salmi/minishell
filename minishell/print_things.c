/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:32:45 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/09 10:36:02 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_full_command(int j, t_token *token)
{
	int i = 0;
	int k = 0;
	int r;
	printf(" ______________________________________________________");
	printf("________________________________________________________ \n");
   while (k++ < j)
   {
		r = ft_strlen(token[i].command);
		printf("|                          |                          |");
		printf("                           |                            |\n");
		printf("|Token[%d] : '%s'", k, token[i].command);
		while (i < 13 - ft_strlen(token[i].command))
		{
			printf(" ");
			i++;
		}
		i = 0;
		printf("|");
		while (i++ < 12)
			printf(" ");
		while (r > 9)
		{
			r = r / 10;
			printf(" ");
		}
		i = 0;
		printf("|");
		printf("Len : %d",  ft_strlen(token[i++].command));
		while (i < 19 - ft_strlen(token[i].command))
		{
			printf(" ");
			i++;
		}
		while (r > 9)
		{
			r = r / 10;
			printf(" ");
		}
		i = 0;
		printf("|");
		printf("State : %s", "GLOBAL");
		printf("              |\n");
		printf("|__________________________|__________________________|");
		printf("___________________________|____________________________| \n");
   }
}

void print_full_command_new(int j, t_list *list)
{
	t_list *tmp;
	tmp = list;
	int i = 0;
	int k = 0;
	int r;
	printf(" ______________________________________________________");
	printf("________________________________________________________ \n");
   while (tmp && k++ < j)
   {
		r = ft_strlen(tmp->content->command);
		printf("|                          |                          |");
		printf("                           |                            |\n");
		printf("|Token[%d] : '%s'", k, tmp->content->command);
		while (i++ < 13 - ft_strlen(tmp->content->command))
			printf(" ");
		i = 0;
		printf("|");
		while (i++ < 12)
			printf(" ");
		while (r > 9)
		{
			r = r / 10;
			printf(" ");
		}
		i = 0;
		printf("|");
		printf("Len : %d",  ft_strlen(tmp->content->command));
		while (i++ < 19 - ft_strlen(tmp->content->command))
			printf(" ");
		while (r > 9)
		{
			r = r / 10;
			printf(" ");
		}
		i = 0;
		printf("|");
		printf("State : %s", "GLOBAL");
		printf("              |\n");
		printf("|__________________________|__________________________|");
		printf("___________________________|____________________________| \n");
		tmp = tmp->next;
   }
}