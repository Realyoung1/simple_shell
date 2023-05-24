#include "shell.h"

/**
 * bfree - this is a function that frees a pointer and NULLs the addresses.
 * @ptm: this is the addressese of the pointer to be free.
 *
 * Return: 1 if frees, otherwise 0
 */

int bfree(void **ptm)
{
	if (ptm && *ptm)
	{
		free(*ptm);
		*ptm = NULL;
		return (1);
	}
	return (0);
}
