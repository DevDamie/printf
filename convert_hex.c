#include "main.h"

unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);

/**
 * convert_x - Converts an unsigned int argument to hex using abcdef
 * and stores it to a buffer contained in a struct.
 *
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers
 * @widt: A width modifier
 * @prec: A precision modifier
 * @lengt: A length modifier
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer
 */
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	unsigned long int num;
	unsigned int ret = 0;
	char *lead = "0x";

	if (lengt == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (lengt == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		ret += convert_ubase(output, num, "0123456789abcdef",
				flags, widt, prec);

	ret += print_neg_widt(output, ret, flags, widt);

	return (ret);
}

/**
 * convert_X - Converts an unsigned int argument to hex using ABCDEF
 * and stores it to a buffer contained in a struct.
 *
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers
 * @widt: A width modifier
 * @prec: A precision modifier
 * @lengt: A length modifier
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	unsigned long int num;
	unsigned int ret = 0;
	char *lead = "0X";

	if (lengt == LONG)
		num = va_arg(args, unsigned long);
	else
		num = va_arg(args, unsigned int);
	if (lengt == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		ret += convert_ubase(output, num, "0123456789ABCDEF",
				flags, widt, prec);

	ret += print_neg_widt(output, ret, flags, widt);

	return (ret);
}
