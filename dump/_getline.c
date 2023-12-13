#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * _getline - custom getline function 
 * @lineptr: pointer to address for storing the chars read
 * @n: size of characters to read
 * @stream: filestream
 * Return: number of bytes read or -1 if unsuccessful
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_index = 0;
	ssize_t bytes_read = 0, i;
	ssize_t total_bytes_read = 0;
	char *line;
	size_t line_size;
	size_t read_size;

	/*if (lineptr == NULL || n == 0)
	{
		*n = BUFFER_SIZE;
		*lineptr = (char *)malloc(BUFFER_SIZE);
		if (*lineptr == NULL)
			return (-1);
	}*/
	line = *lineptr;
	line_size = *n;
	while (1)
	{
		if (buffer_index == 0)
		{
			bytes_read = read(fileno(stream), buffer, BUFFER_SIZE);
			if (bytes_read == -1)
				return (-1); /*read error*/
			total_bytes_read += bytes_read;
		}
		for (i = 0; i < bytes_read; ++i)
		{
			if (buffer[buffer_index + i] == '\n')/*check for newline*/
			{
				read_size = buffer_index + i + 1;
				if (read_size > line_size)
				{
					line_size = read_size * 2;
					line = realloc(line, read_size);
					if (line == NULL)
						return (-1);
					*lineptr = line;
					*n = line_size;
				}
				memcpy(line, buffer, line_size);
				line[line_size -1] = '\0';
				buffer_index = 0; /* reset*/
				return (read_size);
			}
		}
		if (total_bytes_read > (ssize_t)line_size)/*newline not found*/
		{
			line_size = total_bytes_read * 2;
			line = realloc(line, line_size);
			if (line == NULL)
				return (-1);
			*lineptr = line;
			*n = line_size;
		}
		memcpy(line, buffer, line_size);
		line += bytes_read;
		line_size -= bytes_read;
		buffer_index = 0;
	}
	if (total_bytes_read == 0)
		return (-1); /* nothing read*/		

	if (total_bytes_read > (ssize_t)line_size)
	{
		line_size = total_bytes_read * 2;
		line = realloc(line, line_size);
		if (line == NULL)
			return (-1);
		*lineptr = line;
		*n = line_size;
	}
	memcpy(line, buffer, total_bytes_read);
	line[total_bytes_read] = '\0';
	buffer_index = 0;
	return (total_bytes_read);
}
