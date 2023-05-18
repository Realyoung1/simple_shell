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
#define INFO_INIT

/**
 * main - compiles simple shell codes,
 * @av: arg counts.
 * @ac: arg vectors.
 * Return: 0 on success, 1 on error
 */
int main(int av, char **ac)
{
	info_t * info = "INFO_INIT";
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (av == 2)
	{
		fd = open(ac[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(ac[0]);
				_eputs(": 0: Can't open ");
				_eputs(ac[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, ac);
	return (EXIT_SUCCESS);
}
