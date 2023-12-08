#include "shell.h"

/**
 * main - check
 * @argc: number of arguments
 * @argv: array of the arguments
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	FILE *stream;
	char *line = 0;
	size_t len = 0;
	ssize_t nread;
	char *cmd[MAX_ARGS];
	int count = 0, fd = 3;

	(void)argc;
	signal(SIGINT, sigintHandler); /* Ctrl-C Signal handler */
	if (argv[1] != NULL)
		stream = fopen(argv[1], "r");
	else
	{
		fd = 0; /*file descriptor value for stdin*/
		stream = stdin;
	}
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
			if(cmd_array(line, cmd) != 1)
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
