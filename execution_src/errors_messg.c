#include "../includes/minishell.h"

void print_error(char *error_mesage, char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_mesage, 2);
}
