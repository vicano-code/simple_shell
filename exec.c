#include "shell.h"


/**
 * execute_cmd - command execution using execve
 * @cmd: pointer to array of command and arguments
 * @str: execution filename
 * @count: program session command count
 * Return: -1 error 0 -success
 */

int execute_cmd(char **cmd, char *str, int count)
{
	char *cmd_path;
	char *cmd_dir = malloc(sizeof(char *) * MAX_ARGS);
	pid_t pid;
	int status;
	char *s = "not found";

	if (access(cmd[0], X_OK) != 0)/*check if cmd is executable*/
	{
		cmd_path = get_cmd_path(cmd, cmd_dir);
		if (cmd_path == NULL)
		{
			free(cmd_dir);
			_pcerror(str, count, cmd[0], s);
			return (-1);
		}
		cmd[0] = cmd_path;
	}
	/* create child process to run command */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(cmd[0], cmd, environ) == -1)
		{
			free(cmd_dir);
			_pcerror(str, count, cmd[0], s);
			return (-1);
		}
	}
	else
		do
			waitpid(pid, &status, WUNTRACED);
		while
			(!WIFEXITED(status) && !WIFSIGNALED(status));
	free(cmd_dir);
	return (0);
}
