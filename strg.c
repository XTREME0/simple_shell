#include "main.h"

/**
 * _strcpy - strcpy
 * @dest: destination
 * @src: source
 * Return: pointer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - strdup
 * @str: string
 * Return: pointer
 */
char *_strdup(const char *str)
{
	int llen = 0;
	char *rt;

	if (str == NULL)
		return (NULL);
	while (*str++)
		llen++;
	rt = malloc(sizeof(char) * (llen + 1));
	if (!rt)
		return (NULL);
	for (llen++; llen--;)
		rt[llen] = *--str;
	return (rt);
}

/**
 * _puts - puts
 * @str: string
 * Return: nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - putchar
 * @chr: char
 * Return: On success 1.
 */
int _putchar(char chr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buf[i++] = chr;
	return (1);
}
