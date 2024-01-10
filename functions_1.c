#include "shell.h"

/**
 * hsh - main shell loop
 * @inform: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(inf_t *inform, char **av)
{
	ssize_t rr = 0;
	int built = 0;

	while (rr != -1 && built != -2)
	{
		clear_info(inform);
		if (interactive(inform))
			_puts("$ ");
		_eputchar(BUFFER_FLUSH);
		rr = get_input(inform);
		if (rr != -1)
		{
			set_info(inform, av);
			built = find_builtin(inform);
			if (built == -1)
				find_cmd(inform);
		}
		else if (interactive(inform))
			_putchar('\n');
		free_info(inform, 0);
	}
	write_history(inform);
	free_info(inform, 1);
	if (!interactive(inform) && inform->status)
		exit(inform->status);
	if (built == -2)
	{
		if (inform->error_number == -1)
			exit(inform->status);
		exit(inform->error_number);
	}
	return (built);
}

/**
 * find_builtin - finds a builtin command
 * @inform: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *		0 if builtin executed successfully,
 *		1 if builtin found but not successful,
 *		-2 if builtin signals exit()
 */
int find_builtin(inf_t *inform)
{
	int i, built = -1;
	built_in_t builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].tp; i++)
		if (_strcmp(inform->argv[0], builtintbl[i].tp) == 0)
		{
			inform->line_counter++;
			built = builtintbl[i].f(inform);
			break;
		}
	return (built);
}

/**
 * find_cmd - finds a command in PATH
 * @inform: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(inf_t *inform)
{
	char *path = NULL;
	int i, z;

	inform->path = inform->argv[0];
	if (inform->linecounter_flag == 1)
	{
		inform->line_counter++;
		inform->linecounter_flag = 0;
	}
	for (i = 0, z = 0; inform->arg[i]; i++)
		if (!is_delim(inform->arg[i], " \t\n"))
			z++;
	if (!z)
		return;

	path = find_path(inform, _getenv(inform, "PATH="), inform->argv[0]);
	if (path)
	{
		inform->path = path;
		fork_cmd(inform);
	}
	else
	{
		if ((interactive(inform) || _getenv(inform, "PATH=")
			|| inform->argv[0][0] == '/') && is_cmd(inform, inform->argv[0]))
			fork_cmd(inform);
		else if (*(inform->arg) != '\n')
		{
			inform->status = 127;
			print_error(inform, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inform: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(inf_t *inform)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inform->path, inform->argv, get_environ(inform)) == -1)
		{
			free_info(inform, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inform->status));
		if (WIFEXITED(inform->status))
		{
			inform->status = WEXITSTATUS(inform->status);
			if (inform->status == 126)
				print_error(inform, "Permission denied\n");
		}
	}
}
