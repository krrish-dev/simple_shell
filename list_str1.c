#include "shell.h"

/**
 * add_n_end - Adds a node to the end of the list
 * @head: Address of pointer to the head node
 * @str: Str field of the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new node.
 */
list_t *add_n_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_membyte((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strrdup(str);
		if (!new_node->str)
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
 * del_node_at_index - Deletes a node at the given index
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int del_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of the pointer to the head node.
 *
 * Return: Void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * print_list_str - Prints only the str element of a list_t linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_putsinpt(h->str ? h->str : "(nil)");
		_putsinpt("\n");
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * add_n - Adds a node to the start of the list
 * @head: Address of pointer to head node
 * @str: Str field of node
 * @num: Node index used by history
 *
 * Return: Size of the list
 */
list_t *add_n(list_t **head, const char *str, int num)
{
	list_t *nw_head;

	if (!head)
		return (NULL);
	nw_head = malloc(sizeof(list_t));
	if (!nw_head)
		return (NULL);
	_membyte((void *)nw_head, 0, sizeof(list_t));
	nw_head->num = num;
	if (str)
	{
		nw_head->str = _strrdup(str);
		if (!nw_head->str)
		{
			free(nw_head);
			return (NULL);
		}
	}
	nw_head->next = *head;
	*head = nw_head;
	return (nw_head);
}
