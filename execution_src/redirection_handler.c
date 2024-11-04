/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:16:59 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/04 01:24:33 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_access(t_token *cmd, t_env *env)
{
    struct stat stat_buf;

    if (cmd->file->opr[0] == '<')
    {
        if (access(cmd->file->file_name, F_OK) == -1)
        {
            print_error("No such file or directory\n", cmd->file->file_name);
            env->exit_status = 1;
            return (-1);
        }
    }
    stat(cmd->file->file_name, &stat_buf);
    if (S_IFDIR == (S_IFMT & stat_buf.st_mode))
    {
        print_error("is a directory\n", cmd->file->file_name);
        env->exit_status = 1;
        return (-1);
    }
    if (!(stat_buf.st_mode & S_IWUSR) || !(stat_buf.st_mode & S_IRUSR))
    {
        print_error("Permission denied\n", cmd->file->file_name);
        env->exit_status = 1;
        return (-1);
    }
    return (0);
}

int redirection_handler(t_token *cmd, t_env *env)
{
    int fd;
    int i;

    i = 0;
    while (cmd->file)
    {
        if (check_access(cmd, env) != 0)
            return (-1);
        if (!ft_strncmp(cmd->file->opr, ">", ft_strlen(cmd->file->opr)))
        {
            fd = open(cmd->file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
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
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (!ft_strncmp(cmd->file->opr, ">>", ft_strlen(cmd->file->opr)))
        {
            fd = open(cmd->file->file_name, O_WRONLY | O_CREAT | O_APPEND, 066);
            if (fd < 0)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        cmd->file = cmd->file->next;
    }
    return (0);
}
