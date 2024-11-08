/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:59 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/07 14:25:04 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int redirection_handler(t_token *cmd, t_env *env)
{
    int fd;
    int saved_stdout;

    fd = -1;
    while (cmd->file)
    {
        if (!ft_strncmp(cmd->file->opr, ">", ft_strlen(cmd->file->opr)))
        {
            fd = open(cmd->file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                env->exit_status = 1;
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (!ft_strncmp(cmd->file->opr, "<", ft_strlen(cmd->file->opr)))
        {
            fd = open(cmd->file->file_name, O_RDONLY);
            if (fd < 0)
            {
                perror("open");
                env->exit_status = 1;
                return (-1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (!ft_strncmp(cmd->file->opr, ">>", ft_strlen(cmd->file->opr)))
        {
            fd = open(cmd->file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("open");
                env->exit_status = 1;
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        cmd->file = cmd->file->next;
    }
    env->exit_status = 0;
    return (0);
}
