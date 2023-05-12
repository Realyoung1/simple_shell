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
 * get_environ - function returns the strings array copy of our environments.
 * @info: contains the pseudo-arguements to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * Return: Always return absolutely 0
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}
/**
 * _unsetenv - this functions removes the environment variable.
 * @info: contains the pseudo-arguements to pass into a functions,
 * allowing uniform prototypes for the function pointer struct.
 * Return: 1 on delete, 0 otherwise.
 * @var: the string env var property.
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t v = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), v);
			v = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		v++;
	}
	return (info->env_changed);
}

/**
 * _setenv - this function Initialize a new environment variable,
 * or modify an existing one.
 * @info: contains the pseudo-arguements to pass into a functions.
 * allowing uniform prototypes for the function pointer struct.
 * @var: the string env var properties.
 * @value: the string env var value.
 * Return: Always return absolutely 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
