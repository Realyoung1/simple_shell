#include "shell.h"

/**
 * _strcpy - funtions thats copies a string.
 * @dest: the destinations funtions.
 * @src: the funtion source.
 * Return: pointers to destination.
 */
char *_strcpy(char *dest, char *src)
{
	int v = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[v])
	{
		dest[v] = src[v];
		v++;
	}
	dest[v] = 0;
	return (dest);
}

/**
 * _strdup - funtions duplicates a strings.
 * @str: funtions the strings to duplicates.
 * Return: pointers to the duplicated strings.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - funtion prints an input string.
 *@str: the string to be printeds.
 * Return: 0
 */
void _puts(char *str)
{
	int v = 0;

	if (!str)
		return;
	while (str[v] != '\0')
	{
		_putchar(str[v]);
		v++;
	}
}

/**
 * _putchar - funtions writes the character c to stdout.
 * @c: The character to prints.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(1, buf, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buf[v++] = c;
	return (1);
}
