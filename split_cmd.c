#include "shell.h"

/**
 * split_cmd - split command line into an array
 * @cmdLine: command line
 * @args: array to store split commands
 * @delim: delimiter
 * Return: Nothing
 */
void split_cmd(char *cmdLine, char **args, char *delim)
{
	int i;
	char *token;

	i = 0;
	token = strtok(cmdLine, delim);
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	args[i] = NULL;
}

/**
 * cmd_with_semicolon - split command line into an array
 * @argv: Program arguments
 * @line: shell command line input
 * @count: command count
 * Return: Nothing
 */
void cmd_with_semicolon(char **argv, char *line, int count)
{
	int j;
	char *args[MAX_ARGS];
	char *cmd[MAX_ARGS];

	split_cmd(line, args, ";");
	for (j = 0; args[j] != NULL; j++)
	{
		if (cmd_array(args[j], cmd) != 1)
		{
			if (strcmp(cmd[0], "exit") == 0)
			{
				free(line);
				exit_shell(cmd);
			}
			cmds_execution(cmd, argv, count);
		}
	}
}

/**
 * other_cmds_execution - split command line into an array
 * @argv: Program arguments
 * @line: shell command line input
 * @count: command count
 * Return: Nothing
 */
void other_cmds_execution(char **argv, char *line, int count)
{
	char *cmd[MAX_ARGS];

	if (cmd_array(line, cmd) != 1)
	{
		if (strcmp(cmd[0], "exit") == 0)
		{
			free(line);
			exit_shell(cmd);
		}
		cmds_execution(cmd, argv, count);
	}

}
