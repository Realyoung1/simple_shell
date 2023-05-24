#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
extern char **environ;

/**
 * struct liststr - singly linked list.
 * @num: the number fields.
 * @str: a string
 * @next: points to the next nodes.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 *struct passinfo - contains the pseudo-arguements to pass into a functions,
 *allowing uniform prototypes for the function pointer struct.
 *@line_count: the error counts.
 *@err_num: the error code for exit()s.
 *@arg: a string generated from the getline containing the arguements.
 *@argv: an array of strings generated from the arg.
 *@path: a string path for current command.
 *@argc: the argument counts.
 *@env_changed: this is the file on which environ was changed.
 *@status: the return status of the last exec'd commands.
 *@cmd_buf: addresses of pointer to cmd_buf, on if chainings.
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@linecount_flag: if on counts this line of inputs.
 *@fname: the program of the filename.
 *@env: linked lists local copy of environ.
 *@environ: customs modified copy of environ from LL env.
 *@histcount: the history line number counts.
 *@history: the history node.
 *@alias: the alias node.
 *@readfd: the fd from which to read line inputs.
 */
typedef struct passinfo
{
	int err_num;
	int linecount_flag;
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	char *fname;
	list_t *env;
	list_t *history;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	int histcount;
} info_t;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 *struct builtin - it contains a builtin strings and related functions.
 *@type: this is the builtin command flags.
 *@func: the functions.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



/* toem_shloop.c */
int hsh(info_t *, char **);
void fork_cmd(info_t *);
int find_builtin(info_t *);
void find_cmd(info_t *);


/* toem_parser.c */
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);


/* loophsh.c */
int loophsh(char **);


/* toem_errors.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);


/* toem_string.c */
int _strlen(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);


/* toem_string1.c */
char *_strcpy(char *, char *);
void _puts(char *);
char *_strdup(const char *);
int _putchar(char);


/* toem_exits.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);


/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);


/* toem_realloc.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);


/* toem_memory.c */
int bfree(void **);


/* toem_atoi.c */
int _isalpha(int);
int interactive(info_t *);
int is_delim(char, char *);
int _atoi(char *);


/* toem_errors1.c */
int _erratoi(char *);
void remove_comments(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);


/* toem_builtin.c */
int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);


/* toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);


/*toem_getline.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);


/* toem_getinfo.c */
void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);


/* toem_environ.c */
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);
int _setenv(info_t *, char *, char *);


/* toem_getenv.c */
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);


/* toem_history.c */
int build_history_list(info_t *info, char *buf, int linecount);
int read_history(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int renumber_history(info_t *info);


/* toem_lists.c */
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);


/* toem_lists1.c */
size_t print_list(const list_t *);
size_t list_len(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);


/* toem_vars.c */
int replace_alias(info_t *);
int replace_string(char **, char *);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);




#endif
