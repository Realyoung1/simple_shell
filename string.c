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
 * _strlen - wrote this functions returns the length of a strings.
 * @s: the string whose length to check.
 * Return: integer length of string.
 */
int _strlen(char *s)
{
	int v = 0;

	if (!s)
		return (0);
	while (*s++)
		v++;
	return (v);
}

/**
 * _strcmp - functions that performs lexicogarphic comparison of two strangs
 * @s1: the first strang
 * @s2: the second strang
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
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
 * starts_with - functions that check if needle starts with haystack.
 * @haystack: strings to search.
 * @needle: the substrings to find.
 * Return: address of next char of haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - this functions concatenates two strings.
 * @dest: the destination buffers.
 * @src: the source buffers.
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
