#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdin.h>
#include <stdout.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @lengt: The length of the string stored in buffer.
 */

typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int lengt;
} buffer_t;

/**
 * struct converter_s - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */
typedef struct converter_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_t;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

/* Conversion Specifier Functions */
unsigned int convert_char(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_point(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int widt, int prec, unsigned char lengt);

/* Handlers */
unsigned char handle_flags(const char *flags, char *index);
unsigned char handle_lengt(const char *modifier, char *index);
int handle_widt(va_list args, const char *modifier, char *index);
int handle_prec(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int print_widt(buffer_t *output, unsigned int printed,
		unsigned char flags, int widt);
unsigned int print_str_widt(buffer_t *output,
		unsigned char flags, int widt, int prec, int size);
unsigned int print_neg_widt(buffer_t *output, unsigned int printed,
		unsigned char flags, int widt);

/* Helper Functions */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int num);
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int widt, int prec);
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int widt, int prec);

#endif
