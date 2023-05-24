#include "shell.h"

/**
 *_eputs - this function is written to prints an input strings.
 * @str: str is denotes the string to be printeds
 *
 * Return: it Nothing but 0.
 */

void _eputs(char *str)
{
	int v = 0;

	if (!str)
		return;
	while (str[v] != '\0')
	{
		_eputchar(str[v]);
		v++;
	}
}

/**
 * _eputchar - this functions writes the character c to stderr.
 * @c: Ths denotes the character to print.
 *
 * Return: if On success it returns 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(2, buf, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buf[v++] = c;
	return (1);
}

/**
 * _putfd - this functions writes the character c to given fd
 * @c: This denotes the character to print.
 * @fd: The files descriptor to write to.
 *
 * Return: Always On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(fd, buf, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buf[v++] = c;
	return (1);
}

/**
 *_putsfd - this functions prints an input strings.
 * @str: This denotes the string to be printed
 * @fd: the file descriptor to write.
 *
 * Return: the number of charsput.
 */
int _putsfd(char *str, int fd)
{
	int v = 0;

	if (!str)
		return (0);
	while (*str)
	{
		v += _putfd(*str++, fd);
	}
	return (v);
}
