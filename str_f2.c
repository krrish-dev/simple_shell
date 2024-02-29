#include "shell.h"

/**
 * _strrdup - Duplicates a string
 * @str: String to duplicate
 *
 * Return: Pointer to duplicated string or NULL if error
 */
char *_strrdup(const char *str)
{
	int length = 0;
	char *rt;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	rt = malloc(sizeof(char) * (length + 1));
	if (!rt)
		return (NULL);
	for (length++; length--;)
		rt[length] = *--str;
	return (rt);
}

/**
 * _strcopy - Copy string src to dest
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *_strcopy(char *dest, char *src)
{
	int itr = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[itr])
	{
		dest[itr] = src[itr];
		itr++;
	}
	dest[itr] = 0;
	return (dest);
}


/**
 * _putchar - Write a character to stdout.
 * @c: The character to write.
 *
 * Return: On success 1, on error -1.
 */
int _putchar(char c)
{
	static int itr;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || itr >= WRITE_BUF_SIZE)
	{
		write(1, buf, itr);
		itr = 0;
	}
	if (c != BUF_FLUSH)
		buf[itr++] = c;
	return (1);
}

/**
 *_putsinpt - Prints an input string.
 *@str: The input string.
 *
 * Return: None.
 */
void _putsinpt(char *str)
{
	int itr = 0;

	if (!str)
		return;
	while (str[itr] != '\0')
	{
		_putchar(str[itr]);
		itr++;
	}
}
