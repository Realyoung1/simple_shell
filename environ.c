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
 * _myenv - this function prints the current working environ.
 * @info: contains the pseudo-arguments to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * Return: Always return absolutely 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - gets the value of an environ variable
 * @info: contains the pseudo-arguments to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * @name: env var name
 *
 * Return: the value 0.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - this functions initialize a new environ variable,
 * or modify the existing one.
 * @info: contains the pseudo-arguments to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv - Remove an environment variable
 * @info: contains the pseudo-arguments to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * Return: Always return absolutely 0.
 */
int _myunsetenv(info_t *info)
{
	int v;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (v = 1; v <= info->argc; v++)
		_unsetenv(info, info->argv[v]);
	return (0);
}
/**
 * populate_env_list - populates env linked list
 * @info: contains the pseudo-arguments to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * Return: Always return absolutely 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t v;

	for (v = 0; environ[v]; v++)
		add_node_end(&node, environ[v], 0);
	info->env = node;
	return (0);
}
