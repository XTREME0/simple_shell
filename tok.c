#include "main.h"

/**
 * **strttiw - strtk
 * @str: string
 * @sep: sep
 * Return: pointer
 */

char **strttiw(char *str, char *sep)
{
	int i, j, k, m, nmwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!sep)
		sep = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_dlm(str[i], sep) && (is_dlm(str[i + 1], sep) || !str[i + 1]))
			nmwrds++;

	if (nmwrds == 0)
		return (NULL);
	s = malloc((1 + nmwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nmwrds; j++)
	{
		while (is_dlm(str[i], sep))
			i++;
		k = 0;
		while (!is_dlm(str[i + k], sep) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strttiw2 - split str
 * @str: string
 * @sep: sep
 * Return: pointer
 */
char **strttiw2(char *str, char sep)
{
	int i, j, k, m, nmwrds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != sep && str[i + 1] == sep) ||
				    (str[i] != sep && !str[i + 1]) || str[i + 1] == sep)
			nmwrds++;
	if (nmwrds == 0)
		return (NULL);
	s = malloc((1 + nmwrds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nmwrds; j++)
	{
		while (str[i] == sep && str[i] != sep)
			i++;
		k = 0;
		while (str[i + k] != sep && str[i + k] && str[i + k] != sep)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
