#include "shell.h"

/**
 * **strtsw2 - Split string into words with char delim
 * @str: String to split
 * @d: Character delimiter
 * Return: Pointer to array of words
 */
char **strtsw2(char *str, char d)
{
	int itr, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (itr = 0; str[itr] != '\0'; itr++)
		if ((str[itr] != d && str[itr + 1] == d) ||
		    (str[itr] != d && !str[itr + 1]) || str[itr + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (itr = 0, j = 0; j < numwords; j++)
	{
		while (str[itr] == d && str[itr] != d)
			itr++;
		k = 0;
		while (str[itr + k] != d && str[itr + k] && str[itr + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[itr++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtsw - Split string into words
 * @str: String to split
 * @d: Delimiter
 * Return: Pointer to array of words.
 */

char **strtsw(char *str, char *d)
{
	int itr, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (itr = 0; str[itr] != '\0'; itr++)
		if (!is_delimstr(str[itr], d) && (is_delimstr(str[itr + 1], d) ||
			!str[itr + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (itr = 0, j = 0; j < numwords; j++)
	{
		while (is_delimstr(str[itr], d))
			itr++;
		k = 0;
		while (!is_delimstr(str[itr + k], d) && str[itr + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[itr++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
