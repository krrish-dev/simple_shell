#include "shell.h"

/**
 **_strncp - Copy string with max n chars
 *	number of characters.
 *@dest: Destination buffer
 *@src: Source string
 *@n: Max number of chars to copy
 *Return: Pointer to dest
 */
char *_strncp(char *dest, char *src, int n)
{
	int itr, j;
	char *s = dest;

	itr = 0;
	while (src[itr] != '\0' && itr < n - 1)
	{
		dest[itr] = src[itr];
		itr++;
	}
	if (itr < n)
	{
		j = itr;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strcharr - Locate character in string
 *@s: String to search
 *@c: Character to find
 *Return: Pointer to c in s or NULL if not found.
 */
char *_strcharr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 **_strnccat - Concatenate strings with max n chars
 *	up to a secified numbers of bytes.
 *@dest: Destination string
 *@src: Source string
 *@n: Max chars to concatenate
 *Return: Pointer to dest
 */
char *_strnccat(char *dest, char *src, int n)
{
	int itr, j;
	char *s = dest;

	itr = 0;
	j = 0;
	while (dest[itr] != '\0')
		itr++;
	while (src[j] != '\0' && j < n)
	{
		dest[itr] = src[j];
		itr++;
		j++;
	}
	if (j < n)
		dest[itr] = '\0';
	return (s);
}
