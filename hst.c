#include "main.h"

/**
 * get_hst - get history
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hst(info_t *inf)
{
	char *b, *d;

	d = _getenv(inf, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, d);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}

/**
 * w_hist - write history
 * @inf: info
 * Return: 1 success
 */
int w_hist(info_t *inf)
{
	ssize_t fd;
	char *fn = get_hst(inf);
	list_t *n = NULL;

	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (n = inf->history; n; n = n->next)
	{
		_ptsfd(n->str, fd);
		_ptfd('\n', fd);
	}
	_ptfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * r_hist - read history
 * @inf: info
 * Return: history count
 */
int r_hist(info_t *inf)
{
	int i, la = 0, lc = 0;
	ssize_t fd, rln, fsz = 0;
	struct stat st;
	char *buf = NULL, *fn = get_hst(inf);

	if (!fn)
		return (0);

	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsz = st.st_size;
	if (fsz < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsz + 1));
	if (!buf)
		return (0);
	rln = read(fd, buf, fsz);
	buf[fsz] = 0;
	if (rln <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsz; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hst_l(inf, buf + la, lc++);
			la = i + 1;
		}
	if (la != i)
		build_hst_l(inf, buf + la, lc++);
	free(buf);
	inf->histcount = lc;
	while (inf->histcount-- >= HIST_MAX)
		dlt_node_i(&(inf->history), 0);
	rnmb_hist(inf);
	return (inf->histcount);
}

/**
 * build_hst_l - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @lc: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hst_l(info_t *inf, char *buf, int lc)
{
	list_t *n = NULL;

	if (inf->history)
		n = inf->history;
	add_nd_end(&n, buf, lc);

	if (!inf->history)
		inf->history = n;
	return (0);
}

/**
 * rnmb_hist - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int rnmb_hist(info_t *inf)
{
	list_t *n = inf->history;
	int i = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (inf->histcount = i);
}

