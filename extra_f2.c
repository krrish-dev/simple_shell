#include "shell.h"

/**
 * print_err - Prints an error message
 * @info: The parameter & return info struct
 * @estr: String containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_err(info_t *info, char *estr)
{
	_errputs(info->fname);
	_errputs(": ");
	print_deci(info->line_count, STDERR_FILENO);
	_errputs(": ");
	_errputs(info->argv[0]);
	_errputs(": ");
	_errputs(estr);
}

/**
 * print_deci - Function prints a decimal (integer) number (base 10)
 * @input: The input
 * @fd: The filedescriptor to write to
 *
 * Return: Number of characters printed
 */
int print_deci(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int itr, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _errputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (itr = 1000000000; itr > 1; itr /= 10)
	{
		if (_abs_ / itr)
		{
			__putchar('0' + current / itr);
			count++;
		}
		current %= itr;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * rm_comments - Function replaces first instance of '#' with '\0'
 * @buf: Address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int itr;

	for (itr = 0; buf[itr] != '\0'; itr++)
		if (buf[itr] == '#' && (!itr || buf[itr - 1] == ' '))
		{
			buf[itr] = '\0';
			break;
		}
}

/**
 * _errintostr - Converts a str to an int.
 * @s: The string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _errintostr(char *s)
{
	int itr = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (itr = 0;  s[itr] != '\0'; itr++)
	{
		if (s[itr] >= '0' && s[itr] <= '9')
		{
			result *= 10;
			result += (s[itr] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * conv_num - Converter function, a clone of itoa
 * @num: Number
 * @base: Base
 * @flags: Argument flags
 *
 * Return: String
 */
char *conv_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
