#include "shell.h"

/**
 **_memset - fills memory with a constant
 *@ptr: the pointer to the memory area
 *@byte: the byte to fill *s with
 *@b_num: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *ptr, char byte, unsigned int b_num)
{
	unsigned int i;

	for (i = 0; i < b_num; i++)
		ptr[i] = byte;
	return (ptr);
}

/**
 * ffree - frees a string of strings
 * @sstr: string of strings
 */
void ffree(char **sstr)
{
	char **z = sstr;

	if (!sstr)
		return;
	while (*sstr)
		free(*sstr++);
	free(z);
}

/**
 * _realloc - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @old_s: byte size of previous block
 * @new_s: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *p, unsigned int old_s, unsigned int new_s)
{
	char *me;

	if (!p)
		return (malloc(new_s));
	if (!new_s)
		return (free(p), NULL);
	if (new_s == old_s)
		return (p);

	me = malloc(new_s);
	if (!me)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		me[old_s] = ((char *)p)[old_s];
	free(p);
	return (me);
}

/**
 * bfree - frees a pointer and NULL
 * @p: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
