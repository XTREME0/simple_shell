#include "main.h"

/**
 * main - entry point
 * @ac: number of args
 * @av: args
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				i_puts(av[0]);
				i_puts(": 0: Can't open ");
				i_puts(av[1]);
				i_putchar('\n');
				i_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	penv_list(info);
	r_hist(info);
	shell(info, av);
	return (EXIT_SUCCESS);
}
