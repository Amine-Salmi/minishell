#include "../includes/minishell_merg.h"

void execute_piped_commands(t_token *cmd, t_env *env)
{
    int fd[2];
    int pipeLine;
	char *path;
	char *executable_path;
	int status;
	t_env *my_env;
	t_token *head;

	head = cmd;
	pipeLine = -1;

    while (cmd)
    {
		if (cmd->next != NULL)
			pipe(fd);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			if (pipeLine != -1)
			{
				dup2(pipeLine, STDIN_FILENO);
				close(pipeLine);
			}
			if (cmd->next != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			close(fd[0]);
			close(fd[1]);
			// if (cmd->redirection)
			// 	redirection_handler(cmd);
			path = find_path(env);
			executable_path = find_executable_file(cmd->command, path);
			if (execve(executable_path, cmd->arg, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (cmd->pid > 0)
		{
			if (pipeLine != -1)
				close(pipeLine);
			pipeLine = dup(fd[0]);
			close(fd[0]);
			close(fd[1]);
		}
        cmd = cmd->next;
    }
	cmd = head;
	while (cmd)
	{
		if (cmd->pid > 0)
			waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
}

