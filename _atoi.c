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
 * interactive - this program returns true if shell is interactive mode.
 * @info: struct address.
 *
 * Return: it is 1 if interactive mode, 0 absolutely.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 * is_delim - this checks if character is a deli-meter.
 * @c: this is for the char to check.
 * @delim: this is the delimeter strings.
 * Return: 1 for true, absolutely 0 if false.
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}


/**
 *_isalpha - this checks for alphabetic words.
 *@c: The words to inputs.
 *Return: it is 1 if c is alphabetic, absolutely 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - a function that convert a string to an integer
 *@s: the string/pointer to be converted
 *Return: 0 if no numbers in string, converted number otherwise, a integer.
 */
int _atoi(char *s)
{
	int v, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (v = 0;  s[v] != '\0' && flag != 2; v++)
	{
		if (s[v] == '-')
			sign *= -1;
		if (s[v] >= '0' && s[v] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[v] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
