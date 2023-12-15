#include "shell.h"

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
	/*implement the comment # */
	while (token != NULL && strcmp(token, "#") != 0 && strchr(token, '#') == NULL)
	{
		cmd[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	cmd[i] = NULL;
	if (cmd[0] == NULL) /*when input is only empy spaces*/
		return (1);
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
 * _setenv - To set a variable in the shell environment
 * @cmd: pointer to the shell terminal command array
 * Return: 1 if success, -1 fail
 */
int _setenv(char **cmd)
{
	int j = 0;
	char *tok;
	char *arg[MAX_ARGS];

	if (strcmp(cmd[0], "setenv") == 0)
	{
		if (setenv(cmd[1], cmd[2], 1) == -1)
			return (-1);
	}
	else if (strchr(cmd[0], '=') != NULL) /*set variable using '='*/
	{
		tok = strtok(cmd[0], "=");
		while (tok != NULL)
		{
			arg[j] = tok;
			j++;
			tok = strtok(NULL, "=");
		}
		arg[j] = NULL;
		if (setenv(arg[0], arg[1], 1) == -1)
			return (-1);
	}
	return (1);
}

/**
 * _unsetenv - To unset a variable in the shell environment
 * @cmd: pointer to the shell terminal command array
 * Return: 1 if success, -1 fail
 */
int _unsetenv(char **cmd)
{
	if (unsetenv(cmd[1]) == -1)
		return (-1);

	return (1);
}
