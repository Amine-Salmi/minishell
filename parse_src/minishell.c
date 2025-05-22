/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:14:08 by bbadda            #+#    #+#             */
/*   Updated: 2024/11/17 01:49:37 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	g_signal = false;

int	fill_token(char *command, t_token *token, t_env *e)
{
	char	*s;
	t_index	index;
	char	**s_command;
	int		i;

	i = 0;
	token->file = NULL;
	token->herdoc = NULL;
	token->arg = NULL;
	s = add_spaces(command);
	if (syntax_error(s, e))
		return (free(s), 1);
	s_command = parse_split(s, ' ');
	free(s);
	index = max_files_args(s_command);
	allocate_for_me(index, token);
	if (!__is_herdoc(s_command[0]))
		token->command = __env(s_command[0], e);
	else
		token->command = NULL;
	__token(token, s_command, e);
	simple_free(s_command);
	return (0);
}

t_lst	*toke_lexer(char **command, t_env *e)
{
	t_token	*token;
	t_lst	*lst;
	int		i;
	int		size;

	lst = NULL;
	size = 0;
	i = -1;
	while (command[++i])
	{
		token = malloc(sizeof(t_token));
		if (fill_token(command[i], token, e))
			return (free(token), NULL);
		__ft_lstadd_back(&lst, token);
	}
	return (lst);
}

char	**helper_function(char *line)
{
	char	*full_command;
	char	**command;
	char	*handel_tabs;

	handel_tabs = parse_strtrim(line, "\t");
	if (!handel_tabs)
		return (free(line), NULL);
	free(line);
	full_command = parse_strtrim(handel_tabs, " ");
	if (!full_command)
		return (free(handel_tabs), NULL);
	free(handel_tabs);
	if (pipe_error(full_command, parse_strlen(full_command)))
		return (free(full_command), NULL);
	command = parse_split(full_command, '|');
	free(full_command);
	return (command);
}

int	main(int ac, char *av[], char **env)
{
	t_lst	*lst;
	t_env	*my_env;
	char	**command;
	char	*line;

	my_env = init_and_get_env(av, ac, env);
	while (1)
	{
		handler_signal(1);
		line = readline("\033[1;31m-\033[0m  \033[1;32mminishell-0.1$\033[0m ");
		if (!line)
			__put_and_exit(my_env);
		add_history(line);
		command = helper_function(line);
		if (!command)
			continue ;
		lst = toke_lexer(command, my_env);
		simple_free(command);
		if (lst)
			ft_execute(lst, &my_env);
		free_lst(&lst);
		remove_file();
	}
	free_env(&my_env);
	return (0);
}
