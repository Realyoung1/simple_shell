#include "shell.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

/**
 **_memset - functions fills memory with a constant bytes.
 *@s: functions the pointer to the memory area.
 *@b: functions the byte to fill *s with.
 *@n: functions the amount of bytes to be filled.
 *Return: a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int v;

	for (v = 0; v < n; v++)
		s[v] = b;
	return (s);
}

/**
 * ffree - functions that frees a string of strings.
 * @pp: strings of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - functions reallocates a block of memorys.
 * @ptr: functions pointers to previous malloc'ated blocks.
 * @old_size: functions byte size of previous blocks.
 * @new_size: functions byte size of new blocks.
 * Return: pointer to da ol'block nameens.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
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
