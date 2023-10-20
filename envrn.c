#include "main.h"

/**
 * m_env - print env
 * @inf: Structure info
 * Return: Always 0
 */
int m_env(info_t *inf)
{
	p_lst_str(inf->env);
	return (0);
}

/**
 * _getenv - basically getenv
 * @inf: Structure info
 * @na: env var name
 * Return: pointer
 */
char *_getenv(info_t *inf, const char *na)
{
	list_t *n = inf->env;
	char *p;

	while (n)
	{
		p = ss_w(n->str, na);
		if (p && *p)
			return (p);
		n = n->next;
	}
	return (NULL);
}

/**
 * m_setenv - setenv
 * @inf: Structure info
 * Return: Always 0
 */
int m_setenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		i_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * m_unsetenv - remove env
 * @inf: Structure info
 * Return: Always 0
 */
int m_unsetenv(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		i_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv(inf, inf->argv[i]);
	return (0);
}

/**
 * penv_list - populate env list
 * @inf: Structure info
 * Return: Always 0
 */
int penv_list(info_t *inf)
{
	list_t *n = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nd_end(&n, environ[i], 0);
	inf->env = n;
	return (0);
}
