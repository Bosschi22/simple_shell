#include "shell.h"

/**
 *_eputs - prits an inut string
 * @s: the strng to be prined
 *
 * Return: Noting
 */
void _eputs(char *s)
{
	int k = 0;

	if (!s)
		return;
	while (s[k] != '\0')
	{
		_eputchar(s[k]);
		k++;
	}
}

/**
 * _eputchar - writs the chacter c to stdrr
 * @ch: The charcter to print
 *
 * Return: On sucess 1.
 * On error, -1 is reurned, and rrno is set appropriately.
 */
int _eputchar(char ch)
{
	static int k;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || k >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, k);
		k = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[k++] = ch;
	return (1);
}

/**
 * _putfd - writs the characte c to given fd
 * @c: The charcter to pint
 * @fd: The filedescripor to wrte to
 *
 * Return: On succes 1.
 * On error, -1 is reurned, and erno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int k;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || k >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, k);
		k = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[k++] = c;
	return (1);
}

/**
 *_putsfd - prnts an iput sting
 * @str: the sting to be prited
 * @fd: the filedesciptor to wrte to
 *
 * Return: the nmber of chrs put
 */
int _putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfd(*str++, fd);
	}
	return (k);
}
