/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:56 by asalmi            #+#    #+#             */
/*   Updated: 2024/10/21 13:18:57 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    handle_heredoc(t_token *cmd)
{
    int		fd;
    char	*input_line;
    pid_t	pid;
    int		i;
    const char  *heredoc_file;
    int			status;
    // int fd;
    // char *input_line;
    // t_opr *redi;
    // pid_t pid;
    // int i;

    i = 0;
    heredoc_file = "/tmp/herdoc_file.txt";
    pid = fork();
    if (pid == 0)
    {
        fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
		while (cmd->file[i].del)
		{
			while (1)
			{
				input_line = readline("> ");
				if (input_line == NULL)
				{
					free(input_line);
					exit(EXIT_FAILURE);
				}
				if (cmd->file[i].del != NULL && !ft_strcmp(input_line, cmd->file[i].del))
				{
					free(input_line);
					break;
				}
				ft_putendl_fd(input_line, fd);
				free(input_line);
			}
			i++;	
		}
		printf("zeb\n");
		close(fd);
		exit(EXIT_SUCCESS);
    }
	else if (pid > 0)
	{
		close(fd);
		waitpid(pid, &status, 0);
	}
	cmd->file->file_name = ft_strdup(heredoc_file);
}
