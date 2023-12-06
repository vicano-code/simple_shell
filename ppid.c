#include <stdio.h>
#include <unistd.h>

/**
 * _getppid - a program that prints the PID of the parent process
 * Return: pid value
 */

int _getppid(void)
{
	pid_t my_ppid;

	my_ppid = getppid();

	return (my_ppid);
}
