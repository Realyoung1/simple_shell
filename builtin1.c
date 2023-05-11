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
 * _myhistory - this function displays the history list,
 * it has one command by line,
 * preceded with line numbers, starting from 0.
 * @info: contains the pseudo-arguements to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * Return: Always return 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - this functions is to unsets alias to string
 * @info: this is parameter structs.
 * @str: this indicates the string alias
 *
 * Return: Absolutely 0 on success, its 1 on error.
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}


/**
 * set_alias - this function is to sets alias to string.
 * @info: this is the parameter structs.
 * @str: this is the string alias.
 *
 * Return: Absolutely 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * print_alias - this function prints an alias strings.
 * @node: the alias node
 *
 * Return: its absolutely 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * _myalias - this function mimics the alias builtin (man alias).
 * @info: contains the pseudo-arguments to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * Return: Always absolutely 0
 */

int _myalias(info_t *info)
{
	int v = 0;
	char *p = NULL;

	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (v = 1; info->argv[v]; v++)
	{
		p = _strchr(info->argv[v], '=');
		if (p)
			set_alias(info, info->argv[v]);
		else
			print_alias(node_starts_with(info->alias, info->argv[v], '='));
	}
	return (0);
}
