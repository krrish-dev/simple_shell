#include "shell.h"

/**
 * _strcmpare - Compare two strings lexicographically
 * @s1: First string
 * @s2: Second string
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmpare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strlength - Get length of string
 * @s: String to measure length of
 *
 * Return: Number of chars.
 */
int _strlength(char *s)
{
	int itr = 0;

	if (!s)
		return (0);

	while (*s++)
		itr++;
	return (itr);
}

/**
 * _strconcat - concatenates two strings
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: pointer to dest.
 */
char *_strconcat(char *dest, char *src)
{
	char *rt = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rt);
}

/**
 * starts_wchar - Check if string starts with substring
 * @haystack: String to search in
 * @needle: Substring to check for
 *
 * Return: Address of the next char of haystack or NULL
 */
char *starts_wchar(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
