#include "main.h"

/**
 * get_environ - get inviron
 * @inf: structure info
 * Return: Always 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_ch)
	{
		inf->environ = lst_to_strr(inf->env);
		inf->env_ch = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - delete environment var
 * @inf: Structure info
 * Return: 1 
 * @var: variable
 */
int _unsetenv(info_t *inf, char *var)
{
	list_t *n = inf->env;
	size_t i = 0;
	char *p;

	if (!n || !var)
		return (0);

	while (n)
	{
		p = ss_w(n->str, var);
		if (p && *p == '=')
		{
			inf->env_ch = dlt_node_i(&(inf->env), i);
			i = 0;
			n = inf->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (inf->env_ch);
}

/**
 * _setenv - set an environment variable
 * @inf: Structure info
 * @var: variable
 * @val: value
 * Return: Always 0
 */
int _setenv(info_t *inf, char *var, char *val)
{
	char *buf = NULL;
	list_t *n;
	char *p;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	n = inf->env;
	while (n)
	{
		p = ss_w(n->str, var);
		if (p && *p == '=')
		{
			free(n->str);
			n->str = buf;
			inf->env_ch = 1;
			return (0);
		}
		n = n->next;
	}
	add_nd_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_ch = 1;
	return (0);
}
