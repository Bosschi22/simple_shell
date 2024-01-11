#include "shell.h"

/**
 * _myhistory - displays the hstory list, one comand by line, preceded
 *              with lie numers, startng at 0.
 * @inform: Structure contaning potential argments. Ued to maintain
 *        consnt funtion prototype.
 *  Return: Alwas 0
 */
int _myhistory(inf_t *inform)
{
	print_list(inform->hist);
	return (0);
}

/**
 * unset_alias - sets alis to sting
 * @inform: paramter stct
 * @str: the sting alis
 *
 * Return: Alwas 0 on succss, 1 on eror
 */
int unset_alias(inf_t *inform, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(inform->alias),
		get_node_index(inform->alias, node_starts_with(inform->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - set alias to stng
 * @inform: parmeter stuct
 * @str: the sting alias
 *
 * Return: Alays 0 on sucss, 1 on error
 */
int set_alias(inf_t *inform, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(inform, str));

	unset_alias(inform, str);
	return (add_node_end(&(inform->alias), str, 0) == NULL);
}

/**
 * print_alias - prits an alias sting
 * @node: the aias node
 *
 * Return: Always 0 on succss, 1 on err
 */
int print_alias(ls_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = _strchr(node->s, '=');
		for (a = node->s; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimcs the alias bltin (man alias)
 * @inform: Structre containig potenial arguents. Used to maintain
 *          constant function prootype.
 *  Return: Alays 0
 */
int _myalias(inf_t *inform)
{
	int i = 0;
	char *p = NULL;
	ls_t *node = NULL;

	if (inform->argc == 1)
	{
		node = inform->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inform->argv[i]; i++)
	{
		p = _strchr(inform->argv[i], '=');
		if (p)
			set_alias(inform, inform->argv[i]);
		else
			print_alias(node_starts_with(inform->alias, inform->argv[i], '='));
	}

	return (0);
}
