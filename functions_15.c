#include "shell.h"

/**
 * is_chain - test if curent char in bufer is a cain delimter
 * @inform: the paraeter struct
 * @buf: the char bufer
 * @p: adess of current postion in buf
 *
 * Return: 1 if chain delmeter, 0 otherise
 */
int is_chain(inf_t *inform, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		inform->cmd_buffer_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		inform->cmd_buffer_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		inform->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we suld continue chaiing basd on last status
 * @inform: the pameter struct
 * @buf: the chr bufer
 * @p: adres of curent positin in buf
 * @i: stating positin in buf
 * @len: lengh of bf
 *
 * Return: Voi
 */
void check_chain(inf_t *inform, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (inform->cmd_buffer_type == CMD_AND)
	{
		if (inform->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (inform->cmd_buffer_type == CMD_OR)
	{
		if (!inform->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaes an alias in the tokenzed string
 * @inform: the parater struct
 *
 * Return: 1 if replaed, 0 otherise
 */
int replace_alias(inf_t *inform)
{
	int i;
	ls_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inform->alias, inform->argv[0], '=');
		if (!node)
			return (0);
		free(inform->argv[0]);
		p = _strchr(node->s, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inform->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaes vars in the tokenied stri
 * @inform: the parameer struct
 *
 * Return: 1 if replaed, 0 otherise
 */
int replace_vars(inf_t *inform)
{
	int i = 0;
	ls_t *node;

	for (i = 0; inform->argv[i]; i++)
	{
		if (inform->argv[i][0] != '$' || !inform->argv[i][1])
			continue;

		if (!_strcmp(inform->argv[i], "$?"))
		{
			replace_string(&(inform->argv[i]),
				_strdup(convert_number(inform->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inform->argv[i], "$$"))
		{
			replace_string(&(inform->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inform->env, &inform->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inform->argv[i]),
				_strdup(_strchr(node->s, '=') + 1));
			continue;
		}
		replace_string(&inform->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces sting
 * @old: addess of old sting
 * @new: new strng
 *
 * Return: 1 if replced, 0 otherwse
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
