#include "shell.h"

/**
 * list_len - Determines length of linked list.
 * @h: Pointer to 1st node.
 *
 * Return: Size of list.
 */
size_t list_len(const list_t *h)
{
	size_t itr = 0;

	while (h)
	{
		h = h->next;
		itr++;
	}
	return (itr);
}

/**
 * print_list - Prints all elements of a list_t linked list
 * @h: Pointer to the first node.
 *
 * Return: Size of list.
 */
size_t print_list(const list_t *h)
{
	size_t itr = 0;

	while (h)
	{
		_putsinpt(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_putsinpt(h->str ? h->str : "(nil)");
		_putsinpt("\n");
		h = h->next;
		itr++;
	}
	return (itr);
}



/**
 * list_to_str - Returns an array of strings of the list->str
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_str(list_t *head)
{
	list_t *node = head;
	size_t itr = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !itr)
		return (NULL);
	strs = malloc(sizeof(char *) * (itr + 1));
	if (!strs)
		return (NULL);
	for (itr = 0; node; node = node->next, itr++)
	{
		str = malloc(_strlength(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < itr; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcopy(str, node->str);
		strs[itr] = str;
	}
	strs[itr] = NULL;
	return (strs);
}

/**
 * node_s_wchar - Returns a node whose string
 *					starts with a prefix.
 * @node: Pointer to list head
 * @prefix: String to match.
 * @c: the next character after prefix to match
 *
 * Return: Matching node or NULL.
 */
list_t *node_s_wchar(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_wchar(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gt_node_idx - Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: index of the node or -1
 */
ssize_t gt_node_idx(list_t *head, list_t *node)
{
	size_t itr = 0;

	while (head)
	{
		if (head == node)
			return (itr);
		head = head->next;
		itr++;
	}
	return (-1);
}
