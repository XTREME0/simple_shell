#include "main.h"

/**
 * is_chn - is_chain
 * @info: info
 * @buf: buffer
 * @p: address
 * Return: 1
 */
int is_chn(info_t *inf, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chk_chn - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void chk_chn(info_t *inf, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * rplc_al - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rplc_al(info_t *inf)
{
	int i;
	list_t *n;
	char *p;

	for (i = 0; i < 10; i++)
	{
		n = n_strt_w(inf->alias, inf->argv[0], '=');
		if (!n)
			return (0);
		free(inf->argv[0]);
		p = _strchr(n->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * rplc_str - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rplc_vrs(info_t *inf)
{
	int i = 0;
	list_t *n;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;
		if (!_strcmp(inf->argv[i], "$?"))
		{
			rplc_str(&(inf->argv[i]),
					_strdup(c_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			rplc_str(&(inf->argv[i]),
					_strdup(c_number(getpid(), 10, 0)));
			continue;
		}
		n = n_strt_w(inf->env, &inf->argv[i][1], '=');
		if (n)
		{
			rplc_str(&(inf->argv[i]),
					_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		rplc_str(&inf->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * rplc_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rplc_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
