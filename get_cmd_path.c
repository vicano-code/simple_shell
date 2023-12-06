#include "shell.h"

/**
 * get_cmd_path - get the cmd directory path
 * @cmd: pointer to command
 * @cmd_path: pointer to the directory to store cmd directory path
 * Return: the command path or NULL if fail
 */
char *get_cmd_path(char **cmd, char *cmd_path)
{
	char *path = getenv("PATH");
	char *path_copy;
	char *path_token;
	struct stat st;

	path_copy = malloc(sizeof(char *) * strlen(path));
	strcpy(path_copy, path);
	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		strcpy(cmd_path, path_token);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd[0]);
		strcat(cmd_path, "\0");
		if (stat(cmd_path, &st) == 0)
		{
			free(path_copy);
			return (cmd_path);
		}
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
