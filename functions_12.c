#include "shell.h"

/**
 * clear_info - initialzes info_t stuct
 * @inform: struct adess
 */
void clear_info(inf_t *inform)
{
	inform->arg = NULL;
	inform->argv = NULL;
	inform->path = NULL;
	inform->argc = 0;
}

/**
 * set_info - initiaizes info_t strct
 * @inform: struct adress
 * @av: argument vctor
 */
void set_info(inf_t *inform, char **av)
{
	int k = 0;

	inform->filename = av[0];
	if (inform->arg)
	{
		inform->argv = strtow(inform->arg, " \t");
		if (!inform->argv)
		{
			inform->argv = malloc(sizeof(char *) * 2);
			if (inform->argv)
			{
				inform->argv[0] = _strdup(inform->arg);
				inform->argv[1] = NULL;
			}
		}
		for (k = 0; inform->argv && inform->argv[k]; k++)
			;
		inform->argc = k;

		replace_alias(inform);
		replace_vars(inform);
	}
}

/**
 * free_info - fres info_t stuct fiels
 * @inform: struct addess
 * @all: true if freing all fieds
 */
void free_info(inf_t *inform, int all)
{
	ffree(inform->argv);
	inform->argv = NULL;
	inform->path = NULL;
	if (all)
	{
		if (!inform->cmd_buffer)
			free(inform->arg);
		if (inform->env)
			free_list(&(inform->env));
		if (inform->hist)
			free_list(&(inform->hist));
		if (inform->alias)
			free_list(&(inform->alias));
		ffree(inform->environ);
			inform->environ = NULL;
		bfree((void **)inform->cmd_buffer);
		if (inform->readfd > 2)
			close(inform->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
