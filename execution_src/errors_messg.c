/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:52:15 by asalmi            #+#    #+#             */
/*   Updated: 2024/11/15 23:46:40 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *error_mesage, char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_mesage, 2);
}

void	free_double_p(char **dirs)
{
	int	i;

	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
}

void	remove_file(void)
{
	char	*file;

	file = ft_strdup("/tmp/heredoc_file");
	if (!file)
		return ;
	while (1)
	{
		if (access(file, F_OK) == -1)
			break ;
		unlink(file);
		file = rename_file(file);
	}
	free(file);
}
