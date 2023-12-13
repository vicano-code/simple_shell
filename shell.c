#include "shell.h"

/**
 * check_stream - check if stream is stdin or file
 * @args: the program arguments
 * Return: stream
 */
FILE *check_stream(char **args)
{
	FILE *stream;

	if (args[1] != NULL)
	{
		stream = fopen(args[1], "r");
		if (stream == NULL)
		{
			perror("invalid file");
			exit(1);
		}
	}
	else
		stream = stdin;

	return (stream);
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
	stream = check_stream(argv);
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
				if (strcmp(cmd[0], "setenv") == 0 || strcmp(cmd[0], "unsetenv") == 0)
					_setenv(cmd);
				else if (strcmp(cmd[0], "cd") == 0) /* change directory */
					change_dir(cmd, argv[0], count);
				else
					execute_cmd(cmd, argv[0], count); /* execute cmd */
			}
		}
	}
	fclose(stream);
	free(line);
	return (0);
}
