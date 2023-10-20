#include "main.h"

/**
 * _strlen - strlen
 * @s: string
 * Return: int
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - strcmp
 * @s1: string 1
 * @s2: string 2
 * Return: case
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * ss_w - checks if ndl starts with hys
 * @hys: string
 * @ndl: to find
 * Return: address
 */
char *ss_w(const char *hys, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *hys++)
			return (NULL);
	return ((char *)hys);
}

/**
 * _strcat - strcat
 * @dest: destination
 * @src: source
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
