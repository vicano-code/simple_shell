#include "shell.h"

/**
 * _pcerror - print custom error msg
 * @str: program name
 * @n: program command count
 * @c: program input command
 * @s: error description
 * Return: Nothing
 */
void _pcerror(char *str, int n, char *c, char *s)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
	_putchar(':');
	_putchar(' ');
	if (n < 10)
		_putchar(n + '0');
	else
	{
		_putchar(n / 10 + '0');
		_putchar(n % 10 + '0');
	}
	_putchar(':');
	_putchar(' ');
	for (i = 0; c[i] != '\0'; i++)
		_putchar(c[i]);
	_putchar(':');
	_putchar(' ');
	for (i = 0; s[i] != '\0'; i++)
		_putchar(s[i]);
	_putchar('\n');
}
