#include "main.h"

/**
 * _eatoi - str to int
 * @str: string
 * Return: 0
 */
int _eatoi(char *str)
{
	int i = 0;
	unsigned long int r = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			r *= 10;
			r += (str[i] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * p_error - prints an error message
 * @inf: struct info
 * @es: string
 * Return: 0 (success)
 */
void p_error(info_t *inf, char *es)
{
	i_puts(inf->fname);
	i_puts(": ");
	p_d(inf->lc, STDERR_FILENO);
	i_puts(": ");
	i_puts(inf->argv[0]);
	i_puts(": ");
	i_puts(es);
}

/**
 * p_d - print decimal
 * @in: in
 * @fd: fd
 * Return: num of printed chars
 */
int p_d(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, c = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = i_putchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		c++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			c++;
		}
		current %= i;
	}
	__putchar('0' + current);
	c++;

	return (c);
}

/**
 * c_number - itoa
 * @nu: number
 * @ba: base
 * @f: flags
 * Return: string
 */
char *c_number(long int nu, int ba, int f)
{
	static char *arr;
	static char buffer[50];
	char s = 0;
	char *ptr;
	unsigned long n = nu;

	if (!(f & CONVERT_UNSIGNED) && nu < 0)
	{
		n = -nu;
		s = '-';

	}
	arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % ba];
		n /= ba;
	} while (n != 0);

	if (s)
		*--ptr = s;
	return (ptr);
}

/**
 * r_comm - handle comments
 * @buf: buffer
 * Return: Always 0;
 */
void r_comm(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
