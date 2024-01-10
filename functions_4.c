#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int sum = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[sum])
	{
		dest[sum] = src[sum];
		sum++;
	}
	dest[sum] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *s)
{
	int w = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		w++;
	r = malloc(sizeof(char) * (w + 1));
	if (!r)
		return (NULL);
	for (w++; w--;)
		r[w] = *--s;
	return (r);
}

/**
 *_puts - prints an input string
 *@s: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *s)
{
	int x = 0;

	if (!s)
		return;
	while (s[x] != '\0')
	{
		_putchar(s[x]);
		x++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}
