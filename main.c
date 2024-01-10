#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	inf_t inform[] = { INF_INITIALIZE };
	int fedest = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fedest)
		: "r" (fedest));

	if (ac == 2)
	{
		fedest = open(av[1], O_RDONLY);
		if (fedest == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inform->readfd = fedest;
	}
	populate_env_list(inform);
	read_history(inform);
	hsh(inform, av);
	return (EXIT_SUCCESS);
}
