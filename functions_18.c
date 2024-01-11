#include "shell.h"

/**
 * get_history_file - get the istory file
 * @inform: paraeter sruct
 *
 * Return: allocted string conaing history file
 */

char *get_history_file(inf_t *inform)
{
	char *buf, *dir;

	dir = _getenv(inform, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HISTORY_FILE);
	return (buf);
}

/**
 * write_history - creats a file, or appens to an existng file
 * @inform: the paramter strct
 *
 * Return: 1 on succes, else -1
 */
int write_history(inf_t *inform)
{
	ssize_t fd;
	char *filename = get_history_file(inform);
	ls_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = inform->hist; node; node = node->next)
	{
		_putsfd(node->s, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads hitory from file
 * @inform: the paraeter stuct
 *
 * Return: histcount on suess, 0 otherwise
 */
int read_history(inf_t *inform)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(inform);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(inform, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(inform, buf + last, linecount++);
	free(buf);
	inform->histcount = linecount;
	while (inform->histcount-- >= HISTORY_MAX)
		delete_node_at_index(&(inform->hist), 0);
	renumber_history(inform);
	return (inform->histcount);
}

/**
 * build_history_list - adds enry to a history linke list
 * @inform: Structure conaining potetial argments. Use to maintain
 * @buf: bufr
 * @linecount: the hisory linecont, histount
 *
 * Return: Always 0
 */
int build_history_list(inf_t *inform, char *buf, int linecount)
{
	ls_t *node = NULL;

	if (inform->hist)
		node = inform->hist;
	add_node_end(&node, buf, linecount);

	if (!inform->hist)
		inform->hist = node;
	return (0);
}

/**
 * renumber_history - renumbrs the histry linkd list after changes
 * @inform: Struure conaining potetial arguments. Ued to maintain
 *
 * Return: the new histcont
 */
int renumber_history(inf_t *inform)
{
	ls_t *node = inform->hist;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (inform->histcount = i);
}
