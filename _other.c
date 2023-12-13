#include "shell.h"

/**
 * sigintHandler - control the ctrl-c signal handler
 * @signum: not used
 * Return: Nothing
 */
void sigintHandler(int signum)
{
	(void)signum;
	_putchar('\n');
	_putchar('$');
	_putchar(' ');
}

/**
 * cmd_array - put command arguments in array
 * @line: line arguments
 * @cmd: pointer to shell terminal command array
 * Return: 0 or 1
 */
int cmd_array(char *line, char **cmd)
{
	int i = 0;
	char *token;
	char *v = malloc(MAX_ARGS);
	char *s;

	token = strtok(line, " \t\n");
	while (token != NULL && strcmp(token, "#"))
	{
		cmd[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	cmd[i] = NULL;
	/* implement the variable $ response */
	if (cmd[1] != NULL && strchr(cmd[1], '$') != NULL)
	{
		_strcpy(v, cmd[1]);
		s = getenv(v);
		if (s != NULL)
			strcpy(cmd[1], s);
		if (strcmp(v, "$") == 0)
		{
			_getpid();
			free(v);
			return (1);
		}
	}
	free(v);
	return (0);
}

/**
 * exit_shell - exit the shell
 * @cmd: pointer to the command array
 * Return: Nothing
 */
void exit_shell(char **cmd)
{
	if (cmd[1] == NULL || cmd[1] == 0)
		exit(EXIT_SUCCESS);

	else
	{
		WEXITSTATUS(atoi(cmd[1]));
		exit(atoi(cmd[1]));
	}
}

/**
 * _setenv - To implement the setenv & unsetenv in the shell
 * @cmd: pointer to the shell terminal command array
 * Return: Nothing
 */
void _setenv(char **cmd)
{
	if (strcmp(cmd[0], "setenv") == 0)
	{
		if (setenv(cmd[1], cmd[2], 1) == -1)
			printf("setenv: failed");
	}
	else
	{
		if (unsetenv(cmd[1]) == -1)
			printf("unsetenv: failed");
	}
}
