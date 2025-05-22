/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:07:59 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/17 01:03:09 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parent_process_logic(pid_t pid, t_env *env)
{
	int	status;

	handler_signal(0);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		env->exit_status = 1;
		g_signal = true;
	}
}

void	free_file_list(t_opr *file)
{
	t_opr	*tmp;

	while (file)
	{
		tmp = file;
		file = file->next;
		free(tmp->file_name);
		free(tmp->opr);
		free(tmp);
	}
}

char	*rename_file(char *str)
{
	char	*new_str;
	int		j;

	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new_str)
		return (NULL);
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
