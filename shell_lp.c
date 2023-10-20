#include "main.h"

/**
 * shell - main shell
 * @inf: info
 * @av: argument
 * Return: 0 on success
 */
int shell(info_t *inf, char **av)
{
	ssize_t r = 0;
	int b_ret = 0;

	while (r != -1 && b_ret != -2)
	{
		cl_inf(inf);
		if (intrctve(inf))
			_puts("$ ");
		i_putchar(BUF_FLUSH);
		r = get_i(inf);
		if (r != -1)
		{
			set_inf(inf, av);
			b_ret = fnd_builtin(inf);
			if (b_ret == -1)
				fnd_cmd(inf);
		}
		else if (intrctve(inf))
			_putchar('\n');
		free_inf(inf, 0);
	}
	w_hist(inf);
	free_inf(inf, 1);
	if (!intrctve(inf) && inf->status)
		exit(inf->status);
	if (b_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (b_ret);
}

/**
 * fnd_builtin - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int fnd_builtin(info_t *inf)
{
	int i, b_i_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", m_exit},
		{"env", m_env},
		{"help", m_h},
		{"history", myhst},
		{"setenv", m_setenv},
		{"unsetenv", m_unsetenv},
		{"cd", _cd},
		{"alias", my_a},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(inf->argv[0], builtintbl[i].type) == 0)
		{
			inf->lc++;
			b_i_ret = builtintbl[i].func(inf);
			break;
		}
	return (b_i_ret);
}

/**
 * fnd_cmd - finds a command
 * @inf: info
 * Return: nothing
 */
void fnd_cmd(info_t *inf)
{
	char *path = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->lc_flag == 1)
	{
		inf->lc++;
		inf->lc_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!is_dlm(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = fnd_pth(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((intrctve(inf) || _getenv(inf, "PATH=")
					|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			p_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				p_error(inf, "Permission denied\n");
		}
	}
}
