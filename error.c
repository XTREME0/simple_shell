#include "main.h"

/**
 * i_puts - print input
 * @str: string
 * Return: Nothing
 */
void i_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		i_putchar(str[i]);
		i++;
	}
}

/**
 * i_putchar - print char
 * @chr: char
 * Return: 1 On success.
 */
int i_putchar(char chr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buf[i++] = chr;
	return (1);
}

/**
 * _ptfd - writes to fd
 * @c: char
 * @fd: filedescriptor
 * Return: 1 On success
 */
int _ptfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _ptsfd - print input
 * @str: string
 * @fd: filedescriptor
 * Return: the number of chars put
 */
int _ptsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _ptfd(*str++, fd);
	}
	return (i);
}
