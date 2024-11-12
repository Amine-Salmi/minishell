/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:56 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/12 01:12:25 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_readirection(t_opr **file_list, char *opr, char *file_name)
{
	t_opr	*new_opr;
	t_opr	*last;

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

void	process_heredoc(t_herdoc *heredoc, t_env *env, int fd)
{
	char	*input_line;
	char	*exp;

	while (1)
	{
		input_line = readline("> ");
		if (input_line == NULL)
		{
			free(input_line);
			exit(EXIT_FAILURE);
		}
		if (!ft_strcmp(input_line, heredoc->del))
		{
			free(input_line);
			break ;
		}
		if (heredoc->del)
			exp = __env(input_line, env);
		else
			exp = ft_strdup(input_line);
		ft_putendl_fd(exp, fd);
		free(exp);
		free(input_line);
	}
}

void	child_process(t_lst *cmd, t_env *env, char *heredoc_file)
{
	int	fd;

	fd = -1;
	signal(SIGINT, SIG_DFL);
	while (cmd->token->herdoc)
	{
		fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		process_heredoc(cmd->token->herdoc, env, fd);
		close(fd);
		cmd->token->herdoc = cmd->token->herdoc->next;
	}
	env->exit_status = 0;
	exit(env->exit_status = 0);
}

void	handle_heredoc(t_lst *cmd, t_env *env)
{
	char	*heredoc_file;
	pid_t	pid;
	int		fd;
	int		status;
	int		i;

	fd = -1;
	heredoc_file = ft_strdup("/tmp/heredoc_file");
	while (cmd)
	{
		pid = fork();
		if (pid == 0)
			child_process(cmd, env, heredoc_file);
		else if (pid > 0)
			parent_process_logic(pid, &status, env);
		add_readirection(&cmd->token->file, "<", heredoc_file);
		heredoc_file = rename_file(heredoc_file);
		cmd = cmd->next;
	}
	free(heredoc_file);
}
