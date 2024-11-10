/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:56 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/10 18:42:31 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *rename_file(char *str)
{	
	char *new_str;
	int j;

	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new_str)
		return NULL;
	while (str[j])
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = '1';
	new_str[j + 1] = '\0';
	free(str);
	return (new_str);

}

void add_readirection(t_opr **file_list, char *opr, char *file_name)
{
	t_opr *new_opr;
	t_opr *last;

	last = *file_list;
	new_opr = malloc(sizeof(t_opr));
	if (!new_opr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_opr->file_name = ft_strdup(file_name);
	new_opr->opr = ft_strdup(opr);
	new_opr->next = NULL;

	if (!*file_list)
	{
		*file_list = new_opr;
	}
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_opr;
	}
}

void handle_heredoc(t_lst *cmd, t_env *env)
{
	char *input_line;
	char *heredoc_file;
	char *exp;
	int pid;
	int fd;
	int status;
	int i;
	
	fd = -1;
	heredoc_file = ft_strdup("/tmp/heredoc_file");
	while (cmd)
	{	
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			while (cmd->token->herdoc)
			{
				fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
				{
					perror("open");
					exit(EXIT_FAILURE);
				}
				while (1)
				{
					input_line = readline("> ");
					// printf("input_line : %s\n", input_line);
					if (input_line == NULL)
					{
						free(input_line);
						exit(EXIT_FAILURE);
					}
					if (!ft_strcmp(input_line, cmd->token->herdoc->del))
					{
						free(input_line);
						break;
					}
					if (cmd->token->herdoc->expend)
						exp = __env(input_line, env);
					else
						exp = parse_strdup(input_line);
					ft_putendl_fd(exp, fd);
					free(exp);
					free(input_line);
				}
				close(fd);
				cmd->token->herdoc = cmd->token->herdoc->next;
			}
			env->exit_status = 0;
			exit(EXIT_SUCCESS);
		}
		else if (pid > 0)
		{	
			handler_signal(0);
			waitpid(pid, &status, 0);
			if (fd != -1)
				close(fd);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			{
				env->exit_status = 1;
				g_signal = true;
			}
		}
		add_readirection(&cmd->token->file, "<", heredoc_file);
		heredoc_file = rename_file(heredoc_file);
		cmd = cmd->next;
	}
}
