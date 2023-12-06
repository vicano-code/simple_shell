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
 * exit_shell - exit the shell
 * @c: the command
 * Return: Nothing
 */
void exit_shell(char *c)
{
	size_t i = 0;

	while (i < strlen(c))
	{
		if (c[i] == '\n')
			c[i] = '\0';
		i++;
	}
	if (strcmp(c, "exit") == 0)
		exit(0);
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
	char *line = 0;
	size_t len = 0;
	ssize_t nread;
	char *cmd[MAX_ARGS];
	char *token;
	int i, count = 0, fd = 3;

	(void)argc;
	/* Ctrl-C Signal handler */
	signal(SIGINT, sigintHandler);
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

		i = 0;
		token = strtok(line, " \t\n");
		while (token != NULL)
		{
			cmd[i] = token;
			i++;
			token = strtok(NULL, " \t\n");
		}
		cmd[i] = NULL;
		if (nread > 1)
		{
			if (strcmp(cmd[0], "exit") == 0)
			{
				free(line);
				exit(0);
			}
			if (strcmp(cmd[0], "cd") == 0) /* change directory */
				change_dir(cmd, argv[0], count);
			else
				execute_cmd(cmd, argv[0], count); /* execute cmd */
		}
	}
	fclose(stream);
	free(line);
	return (0);
}
