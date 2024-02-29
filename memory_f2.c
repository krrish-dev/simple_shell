#include "shell.h"

/**
 * freep - Frees a pointer and NULLs the address
 * @ptr: Address of pointer variable to free
 *
 * Return: 1 if freed, 0 otherwise
 */
int freep(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
