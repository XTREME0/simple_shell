#include "main.h"

/**
 * intrctve - checks if shell is in interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int intrctve(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_dlm - checks if chr is a delim
 * @chr: the char
 * @dlm: the delimeter
 * Return: 1 if true
 */
int is_dlm(char chr, char *dlm)
{
	while (*dlm)
		if (*dlm++ == chr)
			return (1);
	return (0);
}

