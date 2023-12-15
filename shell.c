#include "shell.h"

/**
 * check_stream - check if stream is stdin or file
 * @args: the program arguments
 * @n: program command count
 * Return: stream
 */
FILE *check_stream(char **args, int n)
{
	FILE *stream;

	if (args[1] != NULL)
	{
		stream = fopen(args[1], "r");
		if (stream == NULL)
		{
			fprintf(stderr, "%s: %d: Can't open %s\n", args[0], n, args[1]);
			exit(127);
		}
	}
	else
		stream = stdin;

	return (stream);
}

/**
 * cmds_execution - check other commands
 * @cmd: shell command line arguments
 * @argv: program executable name
 * @n: shell input command count
 * Return: void
 */
void cmds_execution(char **cmd, char **argv, int n)
{
	if (strcmp(cmd[0], "setenv") == 0 || strchr(cmd[0], '=') != NULL)
		_setenv(cmd);
	else if (strcmp(cmd[0], "unsetenv") == 0)
		_unsetenv(cmd);
	else if (strcmp(cmd[0], "cd") == 0) /* change directory */
		change_dir(cmd, argv[0], n);
	else
		execute_cmd(cmd, argv[0], n); /* execute cmd */
}

/**
 * main - check
 * @argc: number of arguments
 * @argv: array of the arguments
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	FILE *stream;
	char *line = NULL, *cmd[MAX_ARGS];
	size_t len = 0;
	ssize_t nread;
	int count = 0, fd = 3;

	(void)argc;
	signal(SIGINT, sigintHandler); /* Ctrl-C Signal handler */
	signal(SIGTSTP, sigtstpHandler); /*ctrl-Z signal handler*/
	stream = check_stream(argv, count);
	if (stream == stdin)
		fd = 0;
	while (1)
	{
		count++;
		if (isatty(fd) == 1)
			printf("$ "); /*display prompt */
		nread = getline(&line, &len, stream);
		if (nread == -1)
			break;
		if (nread > 1)
		{
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
	}
	fclose(stream);
	free(line);
	return (0);
}
