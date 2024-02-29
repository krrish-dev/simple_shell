#include "shell.h"

/**
 * is_delimstr - Checks if character is a delimeter
 * @c: The char to check
 * @delim: The delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimstr(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}


/**
 *_atoi - Converts a string to an integer
 *@s: The string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int itr, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (itr = 0;  s[itr] != '\0' && flag != 2; itr++)
	{
		if (s[itr] == '-')
			sign *= -1;

		if (s[itr] >= '0' && s[itr] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[itr] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}


/**
 * interact - Returns true if shell is interact mode
 * @info: Struct address
 *
 * Return: 1 if interact mode, 0 otherwise
 */
int interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 *_isalpha - Checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
