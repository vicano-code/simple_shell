#include "shell.h"


/**
 * change_dir - changes the directory to the given directory
 * @cmd: array of the simple shell commands
 * @str: program name
 * @n: program shell command count
 * Return: Nothing
 */
void *change_dir(char **cmd, char *str, int n)
{
	char old_dir[MAX_LINE];
	char new_dir[MAX_LINE];

	if (cmd[1] == NULL || strcmp(cmd[1], "$HOME") == 0)
	{
		cmd[1] = getenv("HOME");
		if (cmd[1] == NULL)
			cmd[1] = getenv("PWD");
	}

	if (strcmp(cmd[1], "-") == 0)
	{
		cmd[1] = getenv("OLDPWD");
		if (cmd[1] == NULL)
			cmd[1] = getenv("PWD");
		printf("%s\n", cmd[1]);
	}
	if (getcwd(old_dir, sizeof(old_dir)) == NULL)
		return (NULL);
	if (chdir(cmd[1]) == -1)
		fprintf(stderr, "%s: %d: %s: can't cd to %s\n", str, n, cmd[0], cmd[1]);
	else
	{
		if (getcwd(new_dir, sizeof(new_dir)) == NULL)
			return (NULL);
		if (setenv("OLDPWD", old_dir, 1) == -1)
			return (NULL);
		if (setenv("PWD", new_dir, 1) == -1)
			return (NULL);
	}
	return (NULL);
}
