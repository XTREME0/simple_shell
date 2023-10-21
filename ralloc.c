#include "main.h"

/**
 * _memset - memset
 * @s: pointer
 * @b: byte
 * @n: filled bytes
 * Return: pointer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees mem
 * @pp: string
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - realloc
 * @pt: pointer
 * @o_size: size of old block
 * @n_size: size of new block
 * Return: pointer
 */
void *_realloc(void *pt, unsigned int o_size, unsigned int n_size)
{
	char *p;

	if (!pt)
		return (malloc(n_size));
	if (!n_size)
		return (free(pt), NULL);
	if (n_size == o_size)
		return (pt);
	p = malloc(n_size);
	if (!p)
		return (NULL);
	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		p[o_size] = ((char *)pt)[o_size];
	free(pt);
	return (p);
}
