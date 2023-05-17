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
 * **strtow - functiosns splits a string into words.
 * Repeat delimiters are ignores.
 * @str: functions the input strings.
 * @d: the delimeter strings.
 * Return: a pointer to an array of strings, or NULL on failures.
 */
char **strtow(char *str, char *d)
{
	int v, j, r, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (v = 0; str[v] != '\0'; v++)
		if (!is_delim(str[v], d) && (is_delim(str[v + 1], d) || !str[v + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (v = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[v], d))
			v++;
		r = 0;
		while (!is_delim(str[v + r], d) && str[v + r])
			r++;
		s[j] = malloc((r + 1) * sizeof(char));
		if (!s[j])
		{
			for (r = 0; r < j; r++)
				free(s[r]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < r; m++)
			s[j][m] = str[v++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - funtions that splits a string into words.
 * @str: the input strings.
 * @d: the delimeters.
 * Return: a pointer to an array of strings, or NULL on failures.
 */
char **strtow2(char *str, char d)
{
	int v, j, r, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (v = 0; str[v] != '\0'; v++)
		if ((str[v] != d && str[v + 1] == d) ||
				(str[v] != d && !str[v + 1]) || str[v + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (v = 0, j = 0; j < numwords; j++)
	{
		while (str[v] == d && str[v] != d)
			v++;
		r = 0;
		while (str[v + r] != d && str[v + r] && str[v + r] != d)
			r++;
		s[j] = malloc((r + 1) * sizeof(char));
		if (!s[j])
		{
			for (r = 0; r < j; r++)
				free(s[r]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < r; m++)
			s[j][m] = str[r++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
