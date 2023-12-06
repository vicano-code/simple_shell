#include <stdio.h>
#include <unistd.h>

/**
 * _getpid - a program that prints the PID of a process
 * Return: 0 - success
 */

int _getpid(void)
{
	pid_t my_pid;

	my_pid = getpid();

	printf("%u", my_pid);
	return (0);
}
