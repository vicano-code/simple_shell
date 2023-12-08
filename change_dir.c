#include "shell.h"


/**
 * change_dir - changes the directory to the given directory
 * @cmd: array of the simple shell commands
 * @str: program name
 * @n: program shell command count
 * Return: Nothing
 */
void change_dir(char **cmd, char *str, int n)
{
	char old_dir[MAX_LINE];
	char new_dir[MAX_LINE];
	char *txt;

	if (cmd[1] == NULL || strcmp(cmd[1], "$HOME") == 0)
		cmd[1] = getenv("HOME");
	if (strcmp(cmd[1], "-") == 0)
	{
		cmd[1] = getenv("OLDPWD");
		printf("%s\n", cmd[1]);
	}
	getcwd(old_dir, sizeof(old_dir));
	if (chdir(cmd[1]) == -1)
	{
		/*txt = malloc(sizeof(char *) * 120);*/
		txt = "cant cd to";
		/*strcat(txt, cmd[1]);*/
		_pcerror(str, n, cmd[1], txt);
	}
	else
	{
		getcwd(new_dir, sizeof(new_dir));
		setenv("OLDPWD", old_dir, 1);
		setenv("PWD", new_dir, 1);
	}
}
