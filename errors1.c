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
 * _erratoi - this a function that convert a string to an integer.
 * @s: the string or ponter to be converted.
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on errors.
 */

int _erratoi(char *s)
{
	int v = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (v = 0;  s[v] != '\0'; v++)
	{
		if (s[v] >= '0' && s[v] <= '9')
		{
			result *= 10;
			result += (s[v] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - the functions prints an error message.
 * @info: this is the parameter & return info struct address.
 * @estr: string containing specified types of error type.
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error absolutely.
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints a decimal (integer) number (base 10) function.
 * @input: the input struct function.
 * @fd: the files descriptor to writes.
 *
 * Return: this returns number of characters printed.
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int v, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (v = 1000000000; v > 1; v /= 10)
	{
		if (_abs_ / v)
		{
			__putchar('0' + current / v);
			count++;
		}
		current %= v;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * convert_number - this is the function that converts a number to any base.
 * @num: numbers to converts.
 * @base: base to converts.
 * @flags: argument flags conversion.
 *
 * Return: strings.
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - this is a function that removes or
 * replaces first instance of '#' with '\0'
 * @buf: address of the string to remove or replace.
 *
 * Return: Absolutely always 0;
 */

void remove_comments(char *buf)
{
	int v;

	for (v = 0; buf[v] != '\0'; v++)
		if (buf[v] == '#' && (!v || buf[v - 1] == ' '))
		{
			buf[v] = '\0';
			break;
		}
}
