#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Macro to use system getline() or custom */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* Macros for I/O buffer sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Macros for number conversion */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Macro for history file path */
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - Node for a singly linked list that stores strings
 *
 * @num: Numeric field to store with node
 * @str: String field to store with node
 * @next: Pointer to next node in list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Data structure to pass information to command functions
 *
 * @arg: Command argument string from user input
 * @argv: Argument array parsed from arg string
 * @path: Path for executing command
 * @argc: Number of arguments in argv
 * @line_count: Counter for command lines executed
 * @err_num: Error number to pass to exit()
 * @linecount_flag: Whether to increment line_count for this command
 * @fname: Program filename for executed command
 * @env: Local copy of environment list
 * @history: History node pointer
 * @alias: Alias node pointer
 * @environ: Custom modified copy of global environ
 * @env_changed: Flag if environ was changed
 * @status: Return status of last executed command
 * @cmd_buf: Pointer to buffer storing chained commands
 * @cmd_buf_type: Type of command chain (AND, OR, SEQUENCE)
 * @readfd: File descriptor to read input from
 * @histcount: Total number of history entries
*/

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 * struct builtin - Structure to represent a builtin command
 *
 * @type: String name of the builtin command
 * @func: Function pointer to the builtin command implementation
*/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* errors_str.c */
void _errputs(char *);
int _errputchar(char);
int _putfiled(char c, int fd);
int _putsfiled(char *str, int fd);

/* funcmd.c */
int hsh_char(info_t *, char **);
int find_built(info_t *);
void find_c(info_t *);
void fork_c(info_t *);

/* funpath.c */
int is_cpath(info_t *, char *);
char *dupli_chars(char *, int, int);
char *find_pstr(info_t *, char *, char *);

/* str_f1.c */
int _strlength(char *);
int _strcmpare(char *, char *);
char *starts_wchar(const char *, const char *);
char *_strconcat(char *, char *);

/* str_f2.c */
char *_strcopy(char *, char *);
char *_strrdup(const char *);
void _putsinpt(char *);
int _putchar(char);

/* str_f3.c */
char *_strncp(char *, char *, int);
char *_strnccat(char *, char *, int);
char *_strcharr(char *, char);

/* str_f4.c */
char **strtsw(char *, char *);
char **strtsw2(char *, char);

/* memory_f1 */
char *_membyte(char *, char, unsigned int);
void str_free(char **);
void *_realcon(void *, unsigned int, unsigned int);

/* memory_f2.c */
int freep(void **);

/* extra_f1.c */
int interact(info_t *);
int is_delimstr(char, char *);
int _isalpha(int);
int _atoi(char *);

/* extra_f2.c */
int _errintostr(char *);
void print_err(info_t *, char *);
int print_deci(int, int);
char *conv_num(long int, int, int);
void rm_comments(char *);

/* get_functions.c module */
ssize_t g_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigHandler(int);

/* builtin_e1.c */
int _myexitsh(info_t *);
int _mychangecd(info_t *);
int _myhelppage(info_t *);

/* builtin_e2.c */
int _mydphistory(info_t *);
int _myaliasb(info_t *);

/* cls.c module */
void cls_info(info_t *);
void setting_info(info_t *, char **);
void frees_info(info_t *, int);

/* file_io_gwrb.c */
char *g_history_file(info_t *info);
int wr_history(info_t *info);
int rd_history(info_t *info);
int bd_history_list(info_t *info, char *buf, int linecount);
int rembar_history(info_t *info);

/* env_f1.c module */
char *_gtenv(info_t *, const char *);
int _mycuenv(info_t *);
int _myinitilizeenv(info_t *);
int _myunsetenviro(info_t *);
int p_env_list(info_t *);

/* env_f2.c module */
char **get_envstrcp(info_t *);
int _rmenv(info_t *, char *);
int _set_env(info_t *, char *, char *);

/* chain_functions.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_vars(info_t *);
int rep_string(char **, char *);

/* list_str1.c module */
list_t *add_n(list_t **, const char *, int);
list_t *add_n_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int del_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* list_str2.c module */
size_t list_len(const list_t *);
char **list_to_str(list_t *);
size_t print_list(const list_t *);
list_t *node_s_wchar(list_t *, char *, char);
ssize_t gt_node_idx(list_t *, list_t *);


#endif
