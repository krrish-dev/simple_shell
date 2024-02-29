#include "shell.h"

/**
 **_membyte - Fills memory with a constant byte.
 *@s: Memory area to fill.
 *@b: Byte to fill memory area with.
 *@n: Number of bytes to fill.
 *Return: Pointer to memory area s
 */
char *_membyte(char *s, char b, unsigned int n)
{
	unsigned int itr;

	for (itr = 0; itr < n; itr++)
		s[itr] = b;
	return (s);
}


/**
 * _realcon - Reallocate memory block.
 * @ptr: Pointer to prev memory block.
 * @old_size: Size in bytes of ptr block.
 * @new_size: New size in bytes of block.
 *
 * Return: Pointer to new block or NULL if error.
 */
void *_realcon(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * str_free - Frees a string of strings.
 * @pp: Null terminated array of strings to free.
 */
void str_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
