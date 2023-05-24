#include "shell.h"
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
 **_strncpy - this is a functtion that copy strings.
 *@dest: this is the destination of the string to copy to.
 *@src: this is the source string to copy from.
 *@n: this is the amounts of characters to be copy.
 *Return: it returns the concatenated strings
 */

char *_strncpy(char *dest, char *src, int n)
{
	int v, b;
	char *s = dest;

	v = 0;
	while (src[v] != '\0' && v < n - 1)
	{
		dest[v] = src[v];
		v++;
	}
	if (v < n)
	{
		b = v;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - this function concatenates two strings.
 *@dest: this is the first string.
 *@src: this is the second string.
 *@n: this is the amount of bytes to be maximally use.
 *Return: this returns the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int v, b;
	char *s = dest;

	v = 0;
	b = 0;
	while (dest[v] != '\0')
		v++;
	while (src[b] != '\0' && b < n)
	{
		dest[v] = src[b];
		v++;
		b++;
	}
	if (b < n)
		dest[v] = '\0';
	return (s);
}

/**
 **_strchr - writes a functions that locates a character in a string.
 *@s: this is the string to be parsed or locates.
 *@c: this is the characters to locate.
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
