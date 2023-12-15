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
 * sigtstpHandler - control the ctrl-Z signal handler
 * @signum: not used
 * Return: Nothing
 */
void sigtstpHandler(int signum)
{
	(void)signum;
}
