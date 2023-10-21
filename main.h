#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for c_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_main.history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - psd
 * @arg: argument
 * @argv: argv
 * @path: PATH var
 * @argc: arg count
 * @lc: line count
 * @err_num: errors
 * @lc_flag: flag
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_ch: on if environ was changed
 * @status: status
 * @cmd_buf: cmd_buf
 * @cmd_buf_type: type
 * @readfd: fd
 * @histcount: history count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lc;
	int err_num;
	int lc_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_ch;
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
 * struct builtin - struct
 * @type: flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int shell(info_t *, char **);
int fnd_builtin(info_t *);
void fnd_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *dup_chr(char *, int, int);
char *fnd_pth(info_t *, char *, char *);

int loopshell(char **);

void i_puts(char *);
int i_putchar(char);
int _ptfd(char c, int fd);
int _ptsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *ss_w(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strttiw(char *, char *);
char **strttiw2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bb_fr(void **);

int intrctve(info_t *);
int is_dlm(char, char *);

int _eatoi(char *);
void p_error(info_t *, char *);
int p_d(int, int);
char *c_number(long int, int, int);
void r_comm(char *);

int m_exit(info_t *);
int _cd(info_t *);
int m_h(info_t *);

int myhst(info_t *);
int my_a(info_t *);

ssize_t get_i(info_t *);
int _getline(info_t *, char **, size_t *);
void s_handl(int);

void cl_inf(info_t *);
void set_inf(info_t *, char **);
void free_inf(info_t *, int);

char *_getenv(info_t *, const char *);
int m_env(info_t *);
int m_setenv(info_t *);
int m_unsetenv(info_t *);
int penv_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_hst(info_t *info);
int w_hist(info_t *info);
int r_hist(info_t *info);
int build_hst_l(info_t *info, char *buf, int linecount);
int rnmb_hist(info_t *info);

list_t *add_nd(list_t **, const char *, int);
list_t *add_nd_end(list_t **, const char *, int);
size_t p_lst_str(const list_t *);
int dlt_node_i(list_t **, unsigned int);
void fff_list(list_t **);

size_t ll_len(const list_t *);
char **lst_to_strr(list_t *);
size_t prt_llst(const list_t *);
list_t *n_strt_w(list_t *, char *, char);
ssize_t gt_nd_i(list_t *, list_t *);

int is_chn(info_t *, char *, size_t *);
void chk_chn(info_t *, char *, size_t *, size_t, size_t);
int rplc_al(info_t *);
int rplc_vrs(info_t *);
int rplc_str(char **, char *);

#endif
