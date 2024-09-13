/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/09/13 12:25:01 by bbadda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenization
// check syntax error
// expended
// change $user by user define
// move "" and ''
int main (int ac, char *av[], char **env)
{
	t_token		*is;
	int 		i;
	int 		j;
	char 		**str;
	char 		**s;
	char		*command;
	t_token		token[1000];
	t_list		*f_cmd;

	
	// f_cmd = (t_list*)malloc(sizeof(t_list));
	while (1)
	{
		// i = 0;
		// while (env[i])
		// {
		// 	printf("env[i] : %s\n", env[i]);
		// 	i++;
		// }
		i = 0;
		command = readline("⑉➤minishell-$");
		add_history(command);
		j = tokenization(command, token);
		while (i < j)
		{
			printf ("j = %d\n", j);
			printf("|Token[%d] : '%s'\n", i, token[i].command);
			i++;
		}
		// printf(" ______________________________________________________");
		// printf("________________________________________________________ \n");
		// print_full_command(j, token);
		if (syntax_error(token, j))
			return (0);
		// get_command(j, token, &f_cmd);
		// __free(&f_cmd);
	}
	return (0);
}
