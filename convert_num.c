#include "main.h"

unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char len);
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char len);
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char len);
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char len);

/**
 * convert_di - Converts an argument to a signed int and
 * stores it to a buffer contained in a struct.
 *
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers
 * @widt: A width modifier
 * @prec: A precision modifier
 * @lengt: A length modifier
 * @output: A buffer_t struct containing a character array
 *
 * Return: The number of bytes stored to the buffer
 */
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	long int d, copy;
	unsigned int ret = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (lengt == LONG)
		d = va_arg(args, long int);
	else
		d = va_arg(args, int);
	if (lengt == SHORT)
		d = (short)d;
	if (SPACE_FLAG == 1 && d >= 0) /* Handle space flag */
		ret += _memcpy(output, &space, 1);
	if (prec <= 0 && NEG_FLAG == 0) /* Handle width  */
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;
		/* Handle plus flag when zero flag is active */
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += _memcpy(output, &plus, 1);
		if (ZERO_FLAG == 1 && d < 0) /*Prints -ve sign when zero flag active*/
			ret += _memcpy(output, &neg, 1);
		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (widt -= count; widt > 0; widt--)
			ret += _memcpy(output, &pad, 1);
	}
	if (ZERO_FLAG == 0 && d < 0) /*Print -ve sign when zero flag not active*/
		ret += _memcpy(output, &neg, 1);
	/* Handle plus flag when zero flag is not active */
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += _memcpy(output, &plus, 1);
	if (!(d == 0 && prec == 0))
		ret += convert_sbase(output, d, "0123456789", flags, 0, prec);
	ret += print_neg_width(output, ret, flags, widt);
	return (ret);
}

/**
 * convert_b - Converts an unsigned int argument to binary
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
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	unsigned int num;

	num = va_arg(args, unsigned int);

	(void)lengt;

	return (convert_ubase(output, num, "01", flags, widt, prec));
}

/**
 * convert_o - Converts an unsigned int to octal and
 * stores it to a buffer contained in a struct.
 *
 * @args: A va_list poinitng to the argument to be converted.
 * @flags: Flag modifiers
 * @widt: A width modifier
 * @prec: A precision modifier
 * @lengt: A length modifier
 * @output: A buffer_t struct containing a character array
 *
 * Return: The number of bytes stored to the buffer
 */
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	unsigned long int num;
	unsigned int ret = 0;
	char zero = '0';

	if (lengt == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (lengt == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, &zero, 1);

	if (!(num == 0 && prec == 0))
		ret += convert_ubase(output, num, "01234567",
				flags, widt, prec);

	ret += print_neg_widt(output, ret, flags, widt);

	return (ret);
}

/**
 * convert_u - Converts an unsigned int argument to decimal and
 * stores it to a buffer contained in a struct.
 *
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers
 * @widt: A width modifier
 * @prec: A precision modifier
 * @lengt: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt)
{
	unsigned long int num;
	unsigned int ret = 0;

	if (lengt == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (lengt == SHORT)
		num = (unsigned short)num;

	if (!(num == 0 && prec == 0))
		ret += convert_ubase(output, num, "0123456789",
				flags, widt, prec);

	ret += print_neg_widt(output, ret, flags, widt);

	return (ret);
}
