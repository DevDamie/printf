#include "main.h"

unsigned int convert_char(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_point(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);

/**
 * convert_char - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @widt: A width modifier.
 * @prec: A precision modifier.
 * @lengt: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_char(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	char c;
	unsigned int ret = 0;

	(void)prec;
	(void)lengt;

	c = va_arg(args, int);

	ret += print_width(output, ret, flags, widt);
	ret += _memcpy(output, &c, 1);
	ret += print_neg_width(output, ret, flags, widt);

	return (ret);
}

/**
 * convert_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @widt: A width modifier.
 * @prec: A precision modifier.
 * @lengt: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	char percent = '%';
	unsigned int ret = 0;

	(void)args;
	(void)prec;
	(void)lengt;

	ret += print_width(output, ret, flags, widt);
	ret += _memcpy(output, &percent, 1);
	ret += print_neg_width(output, ret, flags, widt);

	return (ret);
}

/**
 * convert_point - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @widt: A width modifier.
 * @prec: A precision modifier.
 * @lengt: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_point(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int ret = 0;

	(void)lengt;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	ret += convert_ubase(output, address, "0123456789abcdef",
			flags, widt, prec);
	ret += print_neg_width(output, ret, flags, widt);

	return (ret);
}
