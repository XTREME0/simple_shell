#include "main.h"

/**
 * i_buff - buffer
 * @inf: info
 * @buf: buffer
 * @len: len
 * Return: return
 */
ssize_t i_buff(info_t *inf, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, s_handl);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(inf, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			inf->lc_flag = 1;
			r_comm(*buf);
			build_hst_l(inf, *buf, inf->histcount++);
			{
				*len = r;
				inf->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_i - geti
 * @inf: info
 * Return: return
 */
ssize_t get_i(info_t *inf)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = i_buff(inf, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		chk_chn(inf, buf, &j, i, len);
		while (j < len)
		{
			if (is_chn(inf, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * r_buff - reads a buffer
 * @inf: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t r_buff(info_t *inf, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(inf->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - getline
 * @inf: info
 * @ptr: address
 * @l: length
 *
 * Return: s
 */
int _getline(info_t *inf, char **ptr, size_t *l)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *n_p = NULL, *c;

	p = *ptr;
	if (p && l)
		s = *l;
	if (i == len)
		i = len = 0;

	r = r_buff(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	n_p = _realloc(p, s, s ? s + k : k + 1);
	if (!n_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(n_p, buf + i, k - i);
	else
		_strncpy(n_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = n_p;

	if (l)
		*l = s;
	*ptr = p;
	return (s);
}

/**
 * s_handl - handle ctrl-C
 * @sig_n: signal
 * Return: nothing
 */
void s_handl(__attribute__((unused))int sig_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
