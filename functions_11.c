#include "shell.h"

/**
 * list_len - determnes legth of liked list
 * @h: poiner to fist noe
 *
 * Return: sie of list
 */
size_t list_len(const ls_t *h)
{
	size_t k = 0;

	while (h)
	{
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - reurns an array of stings of the list->str
 * @head: poiter to first nde
 *
 * Return: aray of stings
 */
char **list_to_strings(ls_t *head)
{
	ls_t *node = head;
	size_t k = list_len(head), l;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->s) + 1);
		if (!str)
		{
			for (l = 0; l < k; l++)
				free(strs[l]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->s);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}


/**
 * print_list - prins all eleents of a list_t lined list
 * @h: pointer to frst noe
 *
 * Return: size olist
 */
size_t print_list(const ls_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(convert_number(h->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - rturns node whose sring starts with prefix
 * @node: pointr to list hed
 * @prefix: sting o match
 * @c: the net character after prefi to match
 *
 * Return: match node or nul
 */
ls_t *node_starts_with(ls_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->s, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - get the index of a node
 * @head: pointer to listead
 * @node: pointer to he node
 *
 * Return: index of ode or -1
 */
ssize_t get_node_index(ls_t *head, ls_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}
