#include "../includes/minishell.h"

char *find_executable_file(char *command, char *path)
{
    char *executable_path;
    char **dirs;
    int i;

    dirs = ft_split(path, ':');
    i = 0;
    while (dirs[i])
    {
        executable_path = ft_strjoin(ft_strjoin(dirs[i], "/"), command);
        if (access(executable_path, F_OK | X_OK) == 0)
            return (executable_path);
        free(executable_path);
        i++;
    }
	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
    return (NULL);
}

void execute_piped_commands(t_command *cmd, char **env)
{
    int fd[2];
    int pipeLine;
	char *path;
	char *executable_path;
	int status;
	t_env *my_env;
	t_command *head;

	my_env = copy_env(env);
	head = cmd;
	pipeLine = -1;
    while (cmd)
    {
		if (cmd->next != NULL)
			pipe(fd);
		if (cmd->type == PIPE)
			cmd = cmd->next;
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
			if (cmd->redirection)
				redirection_handler(cmd);
			path = find_path(my_env);
			executable_path = find_executable_file(cmd->command, path);
			if (execve(executable_path, cmd->args, NULL) == -1)
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

// void ft_execute(t_command *cmd, char **env)
// {
// 	printf("----- start -----\n");
// 	execute_piped_commands(cmd, env);
// 	printf("----- end -----\n");
// }
