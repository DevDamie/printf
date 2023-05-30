#include "main.h"

unsigned int print_widt(buffer_t *output, unsigned int printed,
		unsigned char flags, int widt);
unsigned int print_str_widt(buffer_t *output,
		unsigned char flags, int widt, int prec, int size);
unsigned int print_neg_widt(buffer_t *output, unsigned int printed,
		unsigned char flags, int widt);

/**
 * print_widt - Stores leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of characters already printed to output
 *           for a given number specifier.
 * @flags: Flag modifiers.
 * @widt: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_widt(buffer_t *output, unsigned int printed,
		unsigned char flags, int widt)
{
	unsigned int ret = 0;
	char wid = ' ';

	if (NEG_FLAG == 0)
	{
		for (widt -= printed; widt > 0;)
			ret += _memcpy(output, &wid, 1);
	}

	return (ret);
}

/**
 * print_str_widt - Stores leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct containing a character array.
 * @flags: Flag modifiers.
 * @widt: A width modifier.
 * @prec: A precision modifier.
 * @size: The size of the string.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_str_widt(buffer_t *output,
		unsigned char flags, int widt, int prec, int size)
{
	unsigned int ret = 0;
	char wid = ' ';

	if (NEG_FLAG == 0)
	{
		widt -= (prec == -1) ? size : prec;
		for (; widt > 0; widt--)
			ret += _memcpy(output, &wid, 1);
	}

	return (ret);
}

/**
 * print_neg_widt - Stores trailing spaces to a buffer for a '-' flag.
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of bytes already stored to output
 *           for a given specifier.
 * @flags: Flag modifiers.
 * @widt: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_neg_widt(buffer_t *output, unsigned int printed,
		unsigned char flags, int widt)
{
	unsigned int ret = 0;
	char wid = ' ';

	if (NEG_FLAG == 1)
	{
		for (widt -= printed; widt > 0; widt--)
			ret += _memcpy(output, &wid, 1);
	}

	return (ret);
}
