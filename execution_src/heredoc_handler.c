/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:56 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/09 14:19:54 by asalmi           ###   ########.fr       */
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

void handle_heredoc(t_lst *cmd, t_env *env)
{
	char *input_line;
	char *heredoc_file;
	int pid;
	int fd;
	int status;
	int i;
	
	fd = -1;
	heredoc_file = ft_strdup("/tmp/heredoc_file");
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (cmd)
		{	
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
					ft_putendl_fd(input_line, fd);
					free(input_line);
				}
				cmd->token->herdoc = cmd->token->herdoc->next;
			}
			heredoc_file = rename_file(heredoc_file);
			cmd = cmd->next;
		}
		close(fd);
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
	cmd->token->file = malloc(sizeof(t_opr));
	cmd->token->file->opr = ft_strdup("<");
	cmd->token->file->file_name = ft_strdup(heredoc_file);
	cmd->token->file->next = NULL;
}
