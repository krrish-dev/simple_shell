#include "shell.h"

/**
 * _errputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _errputchar(char c)
{
	static int itr;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || itr >= WRITE_BUF_SIZE)
	{
		write(2, buf, itr);
		itr = 0;
	}
	if (c != BUF_FLUSH)
		buf[itr++] = c;
	return (1);
}


/**
 *_putsfiled - Prints an input string
 * @str: The string to be printed
 * @fd: The filedescriptor to write to
 *
 * Return: The number of chars put
 */
int _putsfiled(char *str, int fd)
{
	int itr = 0;

	if (!str)
		return (0);
	while (*str)
	{
		itr += _putfiled(*str++, fd);
	}
	return (itr);
}


/**
 *_errputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _errputs(char *str)
{
	int itr = 0;

	if (!str)
		return;
	while (str[itr] != '\0')
	{
		_errputchar(str[itr]);
		itr++;
	}
}

/**
 * _putfiled - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfiled(char c, int fd)
{
	static int itr;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || itr >= WRITE_BUF_SIZE)
	{
		write(fd, buf, itr);
		itr = 0;
	}
	if (c != BUF_FLUSH)
		buf[itr++] = c;
	return (1);
}
