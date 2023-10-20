#include "main.h"

/**
 * cl_inf - clear info_t
 * @inf: struct inf
 */
void cl_inf(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes info_t struct
 * @inf: struct address
 * @av: argument vector
 */
void set_inf(info_t *inf, char **av)
{
	int i = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = strttiw(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		rplc_al(inf);
		rplc_vrs(inf);
	}
}

/**
 * free_inf - frees info_t struct fields
 * @inf: struct address
 * @all: true if freeing all fields
 */
void free_inf(info_t *inf, int all)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			fff_list(&(inf->env));
		if (inf->history)
			fff_list(&(inf->history));
		if (inf->alias)
			fff_list(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		bb_fr((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}
