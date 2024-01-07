#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define CMD_NORMAL	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_MAX	4096

extern char **environ;


/**
 * struct liststring - singly linked list
 * @n: the number field
 * @s: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int n;
	char *s;
	struct liststring *next;
} ls_t;

/**
 *struct passinf - contains pseudo-args to pass into a function,
 *			allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_counter: the error count
 *@error_number: the error code for exit()s
 *@linecounter_flag: if on count this line of input
 *@filename: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@hist: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buffer: address of pointer to cmd_buf, on if chaining
 *@cmd_buffer_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinf
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_counter;
	int error_number;
	int linecounter_flag;
	char *filename;
	ls_t *env;
	ls_t *hist;
	ls_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buffer_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} inf_t;

#define INF_INITIALIZE \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built_in - contains a builtin string and related function
 *@tp: the builtin command flag
 *@f: the function
 */
typedef struct built_in
{
	char *tp;
	int (*f)(inf_t *);
} built_in_t;

/* functions_1.c */
int hsh(inf_t *, char **);
int find_builtin(inf_t *);
void find_cmd(inf_t *);
void fork_cmd(inf_t *);

/* functions_2.c */
int is_cmd(inf_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(inf_t *, char *, char *);
int loophsh(char **);

/* functions_9.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* functions_3.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* functions_4.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* functions_5.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);

/* functions_6.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* functions_7.c */
int interactive(inf_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* functions_8.c */
int _erratoi(char *);
void print_error(inf_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* functions_13.c */
int _myexit(inf_t *);
int _mycd(inf_t *);
int _myhelp(inf_t *);

/* functions_14.c */
int _myhistory(inf_t *);
int unset_alias(inf_t *, char *);
int set_alias(inf_t *, char *);
int print_alias(ls_t *node);
int _myalias(inf_t *);

/* functions_19.c */
ssize_t input_buf(inf_t *, char **, size_t *);
ssize_t get_input(inf_t *);
ssize_t read_buf(inf_t *, char *, size_t *);
int _getline(inf_t *, char **, size_t *);
void sigintHandler(int);

/* functions_12.c */
void clear_info(inf_t *);
void set_info(inf_t *, char **);
void free_info(inf_t *, int);

/* functions_16.c */
char *_getenv(inf_t *, const char *);
int _myenv(inf_t *);
int _mysetenv(inf_t *);
int _myunsetenv(inf_t *);
int populate_env_list(inf_t *);

/* functions_17.c */
char **get_environ(inf_t *);
int _unsetenv(inf_t *, char *);
int _setenv(inf_t *, char *, char *);

/* functions_18.c */
char *get_history_file(inf_t *inform);
int write_history(inf_t *inform);
int read_history(inf_t *inform);
int build_history_list(inf_t *inform, char *buf, int linecount);
int renumber_history(inf_t *inform);

/* functions_10.c */
ls_t *add_node(ls_t **, const char *, int);
ls_t *add_node_end(ls_t **, const char *, int);
size_t print_list_str(const ls_t *);
int delete_node_at_index(ls_t **, unsigned int);
void free_list(ls_t **);

/* functions_11.c */
size_t list_len(const ls_t *);
char **list_to_strings(ls_t *);
size_t print_list(const ls_t *);
ls_t *node_starts_with(ls_t *, char *, char);
ssize_t get_node_index(ls_t *, ls_t *);

/* functions_15.c */
int is_chain(inf_t *, char *, size_t *);
void check_chain(inf_t *, char *, size_t *, size_t, size_t);
int replace_alias(inf_t *);
int replace_vars(inf_t *);
int replace_string(char **, char *);

#endif
