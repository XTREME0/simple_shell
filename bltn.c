#include "main.h"

/**
 * _myhst - displays the history
 * @inf: Struct info
 *  Return: Always 0
 */
int myhst(info_t *inf)
{
	prt_llst(inf->history);
	return (0);
}

/**
 * unset_a - set alias
 * @inf: struct
 * @s: string
 * Return: 0 on success
*/
int unset_a(info_t *inf, char *s)
{
	char *p, chr;
	int r;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	chr = *p;
	*p = 0;
	r = dlt_node_i(&(inf->alias),
		gt_nd_i(inf->alias, n_strt_w(inf->alias, s, -1)));
	*p = chr;
	return (r);
}

/**
 * set_a - set alias
 * @inf: struct
 * @s: string
 * Return: 0 on success
*/
int set_a(info_t *inf, char *s)
{
	char *p;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_a(inf, s));

	unset_a(inf, s);
	return (add_nd_end(&(inf->alias), s, 0) == NULL);
}

/**
 * print_a - print alias
 * @n: alias node
 * Return: 0 on success
*/
int print_a(list_t *n)
{
	char *ptr = NULL, *t = NULL;

	if (n)
	{
		ptr = _strchr(n->str, '=');
		for (t = n->str; t <= ptr; t++)
		_putchar(*t);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_a - alias
 * @inf: Structure info
 *  Return: Always 0
 */
int my_a(info_t *inf)
{
	int i = 0;
	char *p = NULL;
	list_t *n = NULL;

	if (inf->argc == 1)
	{
		n = inf->alias;
		while (n)
		{
			print_a(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		p = _strchr(inf->argv[i], '=');
		if (p)
			set_a(inf, inf->argv[i]);
		else
			print_a(n_strt_w(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
