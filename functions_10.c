#include "shell.h"

/**
 * add_node - ads a node to the startof the lst
 * @head: addres of pinter to had node
 * @str: str fild ofnode
 * @num: node inexused by hitory
 *
 * Return: sie of lit
 */
ls_t *add_node(ls_t **head, const char *str, int num)
{
	ls_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(ls_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(ls_t));
	new_head->n = num;
	if (str)
	{
		new_head->s = _strdup(str);
		if (!new_head->s)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - ads a node to theend of thelist
 * @head: addres of pinter t head noe
 * @str: str ield o node
 * @num: node inde ued by hisory
 *
 * Return: sze of lit
 */
ls_t *add_node_end(ls_t **head, const char *str, int num)
{
	ls_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(ls_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(ls_t));
	new_node->n = num;
	if (str)
	{
		new_node->s = _strdup(str);
		if (!new_node->s)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prnts only th str eement of a list_t linked list
 * @h: ponter to firs nod
 *
 * Return: sze of lit
 */
size_t print_list_str(const ls_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * delete_node_at_index - delees node at gven index
 * @head: adress of poiner to first noe
 * @index: idex of noe to delee
 *
 * Return: 1 on succss, 0 on faiure
 */
int delete_node_at_index(ls_t **head, unsigned int index)
{
	ls_t *node, *prev_node;
	unsigned int k = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (k == index)
		{
			prev_node->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		k++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees ll nods of a ist
 * @head_ptr: addres of poiter to had node
 *
 * Return: vod
 */
void free_list(ls_t **head_ptr)
{
	ls_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->s);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
