#include "shell.h"

/**
 * get_environ - returs the strng array copy of our envron
 * @inform: Strucure containng potential argments. Used to maintain
 *          constant function prottype.
 * Return: Alwys 0
 */
char **get_environ(inf_t *inform)
{
	if (!inform->environ || inform->env_changed)
	{
		inform->environ = list_to_strings(inform->env);
		inform->env_changed = 0;
	}

	return (inform->environ);
}

/**
 * _unsetenv - Remoe an enviroment variable
 * @inform: Struture containing potential arguents. Used to maintain
 *        constnt function prottype.
 * Return: 1 on delte, 0 otherwise
 * @var: the sting env var proerty
 */
int _unsetenv(inf_t *inform, char *var)
{
	ls_t *node = inform->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->s, var);
		if (p && *p == '=')
		{
			inform->env_changed = delete_node_at_index(&(inform->env), i);
			i = 0;
			node = inform->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inform->env_changed);
}

/**
 * _setenv - Initialie a new envionment variable,
 *             or modiy an existng one
 * @inform: Structure contaiing potential arguments. Used to maintain
 *        constat function prootype.
 * @var: the strig env var prperty
 * @value: the strng env va valu
 *  Return: Alwys 0
 */
int _setenv(inf_t *inform, char *var, char *value)
{
	char *buf = NULL;
	ls_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = inform->env;
	while (node)
	{
		p = starts_with(node->s, var);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = buf;
			inform->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inform->env), buf, 0);
	free(buf);
	inform->env_changed = 1;
	return (0);
}
