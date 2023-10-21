#include "main.h"

/**
 * m_exit - exit
 * @inf: Structure info
 * Return: exit status
 */
int m_exit(info_t *inf)
{
	int check;

	if (inf->argv[1])
	{
		check = _eatoi(inf->argv[1]);
		if (check == -1)
		{
			inf->status = 2;
			p_error(inf, "Illegal number: ");
			i_puts(inf->argv[1]);
			i_putchar('\n');
			return (1);
		}
		inf->err_num = _eatoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _cd - cd command
 * @inf: Structure info
 * Return: Always 0
 */
int _cd(info_t *inf)
{
	char *str, *dir, buffer[1024];
	int chdir_r;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenv(inf, "HOME=");
		if (!dir)
			chdir_r = /* TODO: what should this be? */
				chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
		else
			chdir_r = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chdir_r = chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_r = chdir(inf->argv[1]);
	if (chdir_r == -1)
	{
		p_error(inf, "can't cd to ");
		i_puts(inf->argv[1]), i_putchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * m_h - cd of the process
 * @inf: Structure info
 * Return: Always 0
 */
int m_h(info_t *inf)
{
	char **arg_a;

	arg_a = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_a);
	return (0);
}
