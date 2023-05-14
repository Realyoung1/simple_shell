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
 * list_len - wrotes these that determines length of linked list.
 * @h: the pointer to first nodes.
 *
 * Return: size of linkedlists.
 */
size_t list_len(const list_t *h)
{
	size_t v = 0;

	while (h)
	{
		h = h->next;
		v++;
	}
	return (v);
}

/**
 * list_to_strings - returns an array of strings of the linkedlist->str
 * @head: the pointers to first nodes.
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t v = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !v)
		return (NULL);
	strs = malloc(sizeof(char *) * (v + 1));
	if (!strs)
		return (NULL);
	for (v = 0; node; node = node->next, v++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < v; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[v] = str;
	}
	strs[v] = NULL;
	return (strs);
}
/**
 * print_list - functions prints all elements of a list_t in thelinked list.
 * @h: the pointers to first nodes.
 *
 * Return: size of the linkedlist.
 */
size_t print_list(const list_t *h)
{
	size_t v = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		v++;
	}
	return (v);
}

/**
 * node_starts_with - this returns node whose strings starts with any prefix.
 * @node: pointers to linkedlist heads.
 * @prefix: string to see.
 * @c: next characters after any prefix to see.
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - functions that gets the index of a nodes.
 * @head: the pointers to linkedlist heads.
 * @node: the pointers to the nodes.
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t v = 0;

	while (head)
	{
		if (head == node)
			return (v);
		head = head->next;
		v++;
	}
	return (-1);
}
