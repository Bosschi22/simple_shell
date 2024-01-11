#include "shell.h"

/**
 * _myexit - ets the shel
 * @inform: Structure contaning potential argments. Usd to maintain
 *          constant function protype.
 *  Return: exits wth a given ext stats
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(inf_t *inform)
{
	int exitcheck;

	if (inform->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(inform->argv[1]);
		if (exitcheck == -1)
		{
			inform->status = 2;
			print_error(inform, "Illegal number: ");
			_eputs(inform->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inform->error_number = _erratoi(inform->argv[1]);
		return (-2);
	}
	inform->error_number = -1;
	return (-2);
}

/**
 * _mycd - changes th current direcory of the proess
 * @inform: Strucure contining poential arguents. Used to maintain
 *          consant function prototype.
 *  Return: Alays 0
 */
int _mycd(inf_t *inform)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inform->argv[1])
	{
		dir = _getenv(inform, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(inform, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(inform->argv[1], "-") == 0)
	{
		if (!_getenv(inform, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inform, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(inform, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inform->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(inform, "can't cd to ");
		_eputs(inform->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inform, "OLDPWD", _getenv(inform, "PWD="));
		_setenv(inform, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the crrent directory of th proces
 * @inform: Structure contining potntial argumets. Usd to maintain
 *          consnt function prototype.
 *  Return: Alwys 0
 */
int _myhelp(inf_t *inform)
{
	char **arg_arr;

	arg_arr = inform->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}
