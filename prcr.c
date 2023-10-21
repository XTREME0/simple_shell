#include "main.h"

/**
 * is_cmd - checks if cmd
 * @inf: inf
 * @path: path
 * Return: 1
 */
int is_cmd(info_t *inf, char *path)
{
	struct stat st;

	(void)inf;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chr - dub char
 * @paths: PATH string
 * @strt: index to start
 * @stop: index to stop
 * Return: pointer
 */
char *dup_chr(char *paths, int strt, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = strt; i < stop; i++)
		if (paths[i] != ':')
			buf[k++] = paths[i];
	buf[k] = 0;
	return (buf);
}

/**
 * fnd_pth - finds this cmd in the PATH string
 * @inf: the info struct
 * @paths: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *fnd_pth(info_t *inf, char *paths, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!paths)
		return (NULL);
	if ((_strlen(cmd) > 2) && ss_w(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!paths[i] || paths[i] == ':')
		{
			path = dup_chr(paths, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!paths[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}


/**
 * bb_fr - free pointer
 * @p: pointer
 * Return: 1
 */
int bb_fr(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
