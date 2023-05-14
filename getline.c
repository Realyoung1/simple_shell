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
 * input_buf - this functions inputs buffers the chained commands.
 * @info: the parameters structs.
 * @buf: the addresses of buffer.
 * @len: the addresses of len var.
 * Return: 0 bytes read.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t k = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		k = getline(buf, &len_p, stdin);
#else
		k = _getline(info, buf, &len_p);
#endif
		if (k > 0)
		{
			if ((*buf)[k - 1] == '\n')
			{
				(*buf)[k - 1] = '\0'; /* remove trailing newline */
				k--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = k;
				info->cmd_buf = buf;
			}
		}
	}
	return (k);
}

/**
 * get_input - the this functions gets a line minus the newlines.
 * @info: the parameters structs.
 * Return: 0 bytes reads.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t v, j, len;
	ssize_t k = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	k = input_buf(info, &buf, &len);
	if (k == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = v; /* init new iterator to current buf position */
		p = buf + v; /* get pointer for return */
		check_chain(info, buf, &j, v, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		v = j + 1; /* increment past nulled ';'' */
		if (v >= len) /* reached end of buffer? */
		{
			v = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}
	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (k); /* return length of buffer from _getline() */
}

/**
 * read_buf - this functions reads a buffers the chained commands.
 * @info: parameters structs.
 * @buf: buffers
 * @v: sizes.
 *
 * Return: k.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *v)
{
	ssize_t k = 0;

	if (*v)
		return (0);
	k = read(info->readfd, buf, READ_BUF_SIZE);
	if (k >= 0)
		*v = k;
	return (k);
}
/**
 * _getline - gets the next line of input from STDIN
 * buffers the chained commands.
 * @info: the parameters structs.
 * @ptr: addresses of pointers to buffer, preallocated or NULLs.
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t v, len;
	size_t r;
	ssize_t k = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;

	if (p && length)
		s = *length;
	if (v == len)
		v = len = 0;
	k = read_buf(info, buf, &len);
	if (k == -1 || (k == 0 && len == 0))
		return (-1);
	c = _strchr(buf + v, '\n');
	r = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + r : r + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + v, r - v);
	else
		_strncpy(new_p, buf + v, r - v + 1);
	s += r - v;
	v = r;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks.
 * @sig_num: the signal numbers.
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
