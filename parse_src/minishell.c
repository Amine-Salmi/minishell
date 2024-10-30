/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbadda <bbadda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/10/30 22:59:03 by bbadda           ###   ########.fr       */
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
		else if (s_command[i] &&(cmp(s_command[i], "<") || cmp(s_command[i], ">") 
			|| cmp(s_command[i], ">>")))
			index.i++;
		else if (s_command[i])
			index.k++;
		i++;
	}
	return (index);
}
void	__free2(t_token *token)
{
	int i = 0;
	t_token *tmp;
	tmp = token;
	while (tmp)
	{
		 free(tmp->command);
        for (int i = 0; tmp->arg && tmp->arg[i]; i++)
            free(tmp->arg[i]);
        free(tmp->arg);
        t_opr *file_tmp = tmp->file;
        while (file_tmp)
        {
            free(file_tmp->file_name);
            free(file_tmp->opr);
            t_opr *next_file = file_tmp->next;
            free(file_tmp);
            file_tmp = next_file;
        }
        t_herdoc *herdoc_tmp = tmp->herdoc;
        while (herdoc_tmp)
        {
            free(herdoc_tmp->del);
            free(herdoc_tmp->herdoc);
            t_herdoc *next_herdoc = herdoc_tmp->next;
            free(herdoc_tmp);
            herdoc_tmp = next_herdoc;
        }
        t_token *next_con = tmp->next;
        free(tmp);
        tmp = next_con;
    }
}

t_lst	*toke_lexer(char **command, t_env *e)
{
	t_token		*token;
	t_index		index;
	t_lst		*list;
	int			i;
	int 		size;
	char		**s_command;
	char		*s;

	i = -1;
	list = NULL;
	token = malloc(sizeof(t_token));
	token->file = NULL;
	token->herdoc = NULL;
	while (command[++i])
	{
		s = add_spaces(command[i]);
		syntax_error(s);
		s_command = parse_split(s, ' ');
		free(s);
		index = max_files_args(s_command);
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
			token->arg = (char **)malloc(index.k+1 * sizeof(char *));
		if (!__is_herdoc(s_command[0]))
			token->command = remove_q(s_command[0]);
		else
			token->command = NULL;
		__token(token, s_command, e, index.j, index.i);
		__ft_lstadd_back(&list, token);
		// __free2(token);
	}
	return (list);
}

void	priiint(t_lst *lst)
{
	int	i;
	int	j;

	while (lst)
	{
		for (int p = 0; lst->token->arg[p] ; p++)
			printf("c.arg[%d] : %s\n", 0, lst->token->arg[p] );
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
	(void)av;
	(void)ac;

	char		**command;
	char		*full_command;
	t_lst		*lst;
	t_env		*my_env;

	my_env = NULL;
	my_env = (t_env *)malloc(sizeof(t_env));
	my_env = get_env(env);
	printf("----------> %d\n", my_env->exit_status);
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
		token = toke_lexer(command, my_env);
		if (token)
			ft_execute(token, &my_env);
		// priiint(token);
		free(full_command);
	}
	return (0);
}
