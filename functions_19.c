#include "shell.h"

/**
 * input_buf - bufrs chaid comands
 * @inform: paameter strct
 * @buf: addrss of bufer
 * @len: addres of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(inf_t *inform, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the bufer, fil it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(inform, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			inform->linecounter_flag = 1;
			remove_comments(*buf);
			build_history_list(inform, *buf, inform->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				inform->cmd_buffer = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line mnus the newlin
 * @inform: paraeter stuct
 *
 * Return: bytes red
 */
ssize_t get_input(inf_t *inform)
{
	static char *buf; /* the ';' comand chain bufer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(inform->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = input_buf(inform, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have comands left in the chain bufer */
	{
		j = i; /* init new itertor to current buf postion */
		p = buf + i; /* get poiter for return */

		check_chain(inform, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(inform, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment pas nulled ';'' */
		if (i >= len) /* reached en of buffer? */
		{
			i = len = 0; /* reset position and length */
			inform->cmd_buffer_type = CMD_NORMAL;
		}

		*buf_p = p; /* pass back pointer t current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pas back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reds a bufer
 * @inform: paraeter struct
 * @buf: bufer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(inf_t *inform, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(inform->readfd, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line f input fom STDIN
 * @inform: paramter struct
 * @ptr: addres of pointer to bffer, preallocated o NULL
 * @length: size of prealocated ptr buffer if not NLL
 *
 * Return: s
 */
int _getline(inf_t *inform, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(inform, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - bloks ctrl-C
 * @sig_num: the sigal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
