#include "shell.h"

/**
 * _strcpy - copies a string starting from the second character
 * @dest: destination of copied string
 * @src: string to copy
 * Return: dest
 */

char *_strcpy(char *dest, char *src)
{
	size_t i;

	for (i = 1; i <= strlen(src); i++)
	{
		dest[i - 1] = src[i];
	}
	return (dest);
}

/**
 * _strchr - locates a character in a string
 * @s: pointer to string
 * @c: character to locate
 * Return: a pointer to the first occurrence of the character c
 * in the string s, or NULL if the character is not found
 */

char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; *(s + i) != '\n'; i++)
	{
		if (*(s + i) == c)
		{
			return (s + i);
		}
	}

	return (NULL);
}
