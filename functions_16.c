#include "shell.h"

/**
 * _myenv - prints the curent environent
 * @inform: Strucure contaiing potetial arguents. Usd to maintain
 *          constant funcion prototpe.
 * Return: Alwys 0
 */
int _myenv(inf_t *inform)
{
	print_list_str(inform->env);
	return (0);
}

/**
 * _getenv - gets the alue of an eniron variale
 * @inform: Strucure contaning potntial argumnts. Used to maintain
 * @name: env vr nme
 *
 * Return: the vaue
 */
char *_getenv(inf_t *inform, const char *name)
{
	ls_t *node = inform->env;
	char *p;

	while (node)
	{
		p = starts_with(node->s, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initiaize a new envirnment varible,
 *             or modfy an exising one
 * @inform: Strucure containng potenial aruments. Used o maintain
 *        constant fuction protoype.
 *  Return: Alwas 0
 */
int _mysetenv(inf_t *inform)
{
	if (inform->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inform, inform->argv[1], inform->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remve an envinment varible
 * @inform: Strcure contining poential arguents. Used to maintain
 *        constnt function prootype.
 *  Return: Alwys 0
 */
int _myunsetenv(inf_t *inform)
{
	int i;

	if (inform->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inform->argc; i++)
		_unsetenv(inform, inform->argv[i]);

	return (0);
}

/**
 * populate_env_list - popultes env linked list
 * @inform: Structure containing potentil argumnts. Used to maintain
 *          consant functon prototype.
 * Return: Always 0
 */
int populate_env_list(inf_t *inform)
{
	ls_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	inform->env = node;
	return (0);
}
