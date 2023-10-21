#include "main.h"

/**
 * ll_len - list len
 * @h: pointer to nn
 * Return: size
 */
size_t ll_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * lst_to_strr - list to str
 * @head: pointer
 * Return: str
 */
char **lst_to_strr(list_t *head)
{
	list_t *nn = head;
	size_t i = ll_len(head), j;
	char **strings;
	char *s;

	if (!head || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; nn; nn = nn->next, i++)
	{
		s = malloc(_strlen(nn->str) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		s = _strcpy(s, nn->str);
		strings[i] = s;
	}
	strings[i] = NULL;
	return (strings);
}


/**
 * prt_llst - print list
 * @h: pointer
 * Return: size
 */
size_t prt_llst(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(c_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * n_strt_w - returns node starting with prefix
 * @nn: pointer
 * @prfx: string
 * @c: the next char in prfx
 * Return: return
 */
list_t *n_strt_w(list_t *nn, char *prfx, char c)
{
	char *p = NULL;

	while (nn)
	{
		p = ss_w(nn->str, prfx);
		if (p && ((c == -1) || (*p == c)))
			return (nn);
		nn = nn->next;
	}
	return (NULL);
}

/**
 * gt_nd_i - gets the index
 * @h: pointer
 * @nn: node
 *
 * Return: index of nn or -1
 */
ssize_t gt_nd_i(list_t *h, list_t *nn)
{
	size_t i = 0;

	while (h)
	{
		if (h == nn)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
