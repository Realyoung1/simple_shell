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
 * is_chain - functions thats test if current char in buffer
 * is a chain delimeter.
 * @info: the parameter structs.
 * @buf: the char buffers.
 * @p: address of current position in buf.
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
 * check_chain - functions checks we should continue
 * chaining based on last status
 * @info: the parameter structs.
 * @buf: the char buffers.
 * @p: address of current position in bufs.
 * @v: starting position in bufs.
 * @len: length of bufs.
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t v, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[v] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[v] = 0;
			j = len;
		}
	}
	*p = j;
}
/**
 * replace_alias - this functions replaces an aliases in the tokenized string.
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int v;
	list_t *node;
	char *p;

	for (v = 0; v < 10; v++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - this functions replaces vars in the tokenized string.
 * @info: the parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int v = 0;

	list_t *node;

	for (v = 0; info->argv[v]; v++)
	{
		if (info->argv[v][0] != '$' || !info->argv[v][1])
			continue;
	if (!_strcmp(info->argv[v], "$?"))
	{
		replace_string(&(info->argv[v]),
				_strdup(convert_number(info->status, 10, 0)));
		continue;
	}
	if (!_strcmp(info->argv[v], "$$"))
	{
		replace_string(&(info->argv[v]),
				_strdup(convert_number(getpid(), 10, 0)));
		continue;
	}
	node = node_starts_with(info->env, &info->argv[v][1], '=');
	if (node)
	{
		replace_string(&(info->argv[v]),
				_strdup(_strchr(node->str, '=') + 1));
		continue;
	}
	replace_string(&info->argv[v], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - functions that replaces string.
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);

	*old = new;

	return (1);
}
