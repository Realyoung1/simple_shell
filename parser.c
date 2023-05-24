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
 * is_cmd - function that determines if a file is an executable command.
 * @info: the info struct.
 * @path: path to the file.
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - function that duplicates characters.
 * @pathstr: the PATH string.
 * @start: starting index.
 * @stop: stopping index.
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int v = 0, k = 0;

	for (k = 0, v = start; v < stop; v++)
		if (pathstr[v] != ':')
			buf[k++] = pathstr[v];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - function finds this cmd in the PATH strings.
 * @info: the info struct.
 * @pathstr: the PATH string.
 * @cmd: the cmd to find.
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int v = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[v] || pathstr[v] == ':')
		{

			path = dup_chars(pathstr, curr_pos, v);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[v])
				break;
			curr_pos = v;
		}
		v++;
	}
	return (NULL);
}
