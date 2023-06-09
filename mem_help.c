#include "main.h"

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int num);
void free_buffer(buffer_t *output);
buffer_t *init_buffer(void);

/**
 * _memcpy - Copies n bytes from memory area src to
 *           the buffer contained in a buffer_t struct.
 * @output: A buffer_t struct.
 * @src: A pointer to the memory area to copy.
 * @num: The number of bytes to be copied.
 *
 * Return: The number of bytes copied.
 */
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int num)
{
	unsigned int index;

	for (index = 0; index < num; index++)
	{
		*(output->buffer) = *(src + index);
		(output->lengt)++;

		if (output->lengt == 1024)
		{
			write(1, output->start, output->lengt);
			output->buffer = output->start;
			output->lengt = 0;
		}

		else
			(output->buffer)++;
	}

	return (num);
}

/**
 * free_buffer - Frees a buffer_t struct.
 * @output: The buffer_t struct to be freed.
 */
void free_buffer(buffer_t *output)
{
	free(output->start);
	free(output);
}

/**
 * init_buffer - Initializes a variable of struct type buffer_t.
 *
 * Return: A pointer to the initialized buffer_t.
 */
buffer_t *init_buffer(void)
{
	buffer_t *output;

	output = malloc(sizeof(buffer_t));
	if (output == NULL)
		return (NULL);

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buffer;
	output->lengt = 0;

	return (output);
}
