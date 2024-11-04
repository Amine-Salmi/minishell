/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/04 01:31:57 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_index	max_files_args(char **s_command)
{
	t_index	index;
	int		i;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	i = 0;
	while (s_command[i])
	{
		if (cmp(s_command[i], "<<"))
			index.j++;
		else if (s_command[i] && (cmp(s_command[i], "<")
				|| cmp(s_command[i], ">") || cmp(s_command[i], ">>")))
			index.i++;
		else if (s_command[i])
			index.k++;
		i++;
	}
	return (index);
}

void	allocate_for_me(t_index index, t_token *token)
{
	if (index.j > 0)
	{
		token->herdoc = malloc(index.j * sizeof(t_herdoc));
		token->herdoc->del = NULL;
		token->herdoc->herdoc = NULL;
	}
	if (index.i > 0)
	{
		token->file = malloc(index.i * sizeof(t_opr));
		token->file->file_name = NULL;
		token->file->opr = NULL;
	}
	if (index.k > 0)
		token->arg = malloc((index.k + 1)  * sizeof(char *));

}

int	fill_token(char	*command, t_token *token, t_env *e)
{
	char		*s;
	t_index		index;
	char		**s_command;
	int			i;

	i = 0;
	token->file = NULL; 
	token->herdoc = NULL;
	token->arg = NULL;
	s = add_spaces(command);
	if (syntax_error(s))
		return (1);
	s_command = parse_split(s, ' ');
	// an argument adding for no reason after pipe
	// printf("k = %d\n", index.k);
	// for (int y = 0; s_command[y]; y++)
		// printf("s_command[%d] : '%s'\n", y, s_command[y]);
	// i will fix it
	free(s);
	index = max_files_args(s_command);
	allocate_for_me(index, token);
	if (!__is_herdoc(s_command[0]))
		token->command = check_and_replace_env(s_command[0], e);
	else
		token->command = NULL;
	__token(token, s_command, e);
	simple_free(s_command);
	return (0);
}

t_lst	*toke_lexer(char **command, t_env *e)
{
	t_token		*token;
	t_lst		*lst;
	int			i;
	int			size;

	lst = NULL;
	i = -1;
	while (command[++i])
	{
		token = malloc(sizeof(t_token));
		if (fill_token(command[i], token, e))
			return (NULL);
		__ft_lstadd_back(&lst, token);
	}
	return (lst);
}

void	priiint(t_lst *lst)
{
	int	i;
	int	j;
	int	p;

	while (lst)
	{
		printf("cmd : %s\n", lst->token->command);
		p = 0;
		while (lst->token->arg[p])
		{
			printf("c.arg[%d] : %s\n", p, lst->token->arg[p]);
			p++;
		}
		t_opr *tmp2 = lst->token->file;
		while (tmp2)
		{
			printf("file name : %s\n", tmp2->file_name);
			printf("opr       : %s\n", tmp2->opr);
			tmp2 = tmp2->next;
		}
		t_herdoc *tmp1 = lst->token->herdoc;
		while(tmp1)
		{
			printf("herdoc : %s\n", tmp1->herdoc);
			printf("del       : %s\n", tmp1->del);
			tmp1 = tmp1->next;
		}
		lst = lst->next;
	}
}

int main (int ac, char *av[], char **env)
{
	t_lst		*lst;
	t_env		*my_env;
	char		**command;
	char		*full_command;
	int			i;
	(void)av;
	(void)ac;

	my_env = NULL;
	my_env = (t_env *)malloc(sizeof(t_env));
	my_env = get_env(env);
	handler_signal(1);
	while (1)
	{
		full_command = readline("\033[1;31m-\033[0m  \033[1;32mminishell-0.1$\033[0m ");
		if (!full_command)
			break;
		add_history(full_command);
		if (pipe_error(full_command, parse_strlen(full_command)))
			continue ;
		command = parse_split(full_command, '|');
		lst = toke_lexer(command, my_env);
		// priiint(lst);
		if (lst)
			ft_execute(lst, &my_env);
		// printf("EXIT_STATUS ==> %d\n", my_env->exit_status);
		free(full_command);
	}
	return (0);
}
