#include "monty.h"

/**
 * san_buffer()- sanitizes buffer
 * @buff: the source buffer
 *
 * Return: no return
 */

void san_buffer(char *buff)
{
	int i;

	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			buff[i] = '\0';
		i++;
	}
}

/**
 * clear_buffer()- clears  buffer
 * @buffer: buffer that needs clearing
 *
 * Return: no return
 */

void clean_buffer(char *buffer)
{
	int len, i;

	len = strlen(buffer);
	for (i = 0; i < len; i++)
	{
		if (buffer[i] != '\0')
		{
			buffer[i] = '\0';
		}
	}
}

void print_tokens(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}
