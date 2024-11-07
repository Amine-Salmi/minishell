/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:56 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/07 02:52:28 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void rename_file(char **str, int i)
// {	
// 	int k;

// 	str = malloc(sizeof(char *) * (ft_strlen(*str) + i));
// 	if (!str)
// 		return ;
// 	k = 0;
// 	while (str[k])
// 		k++;
// 	str[k] = '0';
// 	str[k++] = '\0';
// }

void handle_heredoc(t_lst *cmd)
{
	char *input_line;
	char *heredoc_file;
	int pid;
	int fd;
	int status;
	int i;
	
	fd = -1;
	i = 0;
	heredoc_file = ft_strdup("/tmp/heredoc_file.txt");
	pid = fork();
	if (pid == 0)
	{
		while (cmd)
		{
			// rename_file(heredoc_file, i++);
			printf("after: %s\n", heredoc_file);
			fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			while (cmd->token->herdoc)
			{
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
			cmd = cmd->next;
		}
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{	
		if (fd != -1)
			close(fd);
		waitpid(pid, &status, 0);
	}
	// cmd->token->file = malloc(sizeof(t_opr));
	// cmd->token->file->opr = ft_strdup("<");
	// cmd->token->file->file_name = ft_strdup("/tmp/heredoc_file.txt");
	// cmd->token->file->next = NULL;
	// printf("file name: %s\n", cmd->token->file->file_name);
	// printf("opr : %s\n", cmd->token->file->opr);
}
// }
// void    handle_heredoc(t_token *cmd)
// {
//     int		fd;
//     char	*input_line;
//     pid_t	pid;
//     int		i;
//     const char  *heredoc_file;
//     int			status;
//     // int fd;
//     // char *input_line;
//     // t_opr *redi;
//     // pid_t pid;
//     // int i;

//     i = 0;
//     heredoc_file = "/tmp/herdoc_file.txt";
//     pid = fork();
//     if (pid == 0)
//     {
//         fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if(fd < 0)
//         {
//             perror("open");
//             exit(EXIT_FAILURE);
//         }
// 		while (cmd->file[i].del)
// 		{
// 			while (1)
// 			{
// 				input_line = readline("> ");
// 				if (input_line == NULL)
// 				{
// 					free(input_line);
// 					exit(EXIT_FAILURE);
// 				}
// 				if (cmd->file[i].del != NULL && !ft_strcmp(input_line, cmd->file[i].del))
// 				{
// 					free(input_line);
// 					break;
// 				}
// 				ft_putendl_fd(input_line, fd);
// 				free(input_line);
// 			}
// 			i++;	
// 		}
// 		close(fd);
// 		exit(EXIT_SUCCESS);
//     }
// 	else if (pid > 0)
// 	{
// 		close(fd);
// 		waitpid(pid, &status, 0);
// 	}
// 	cmd->file->file_name = ft_strdup(heredoc_file);
// }
