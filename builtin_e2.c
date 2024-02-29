#include "shell.h"

/**
 * _mydphistory - Displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mydphistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Sets alias to string
 * @info: Parameter struct
 * @str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *po, c;
	int ret;

	po = _strcharr(str, '=');
	if (!po)
		return (1);
	c = *po;
	*po = 0;
	ret = del_node_at_index(&(info->alias),
		gt_node_idx(info->alias, node_s_wchar(info->alias, str, -1)));
	*po = c;
	return (ret);
}

/**
 * set_alias - Sets alias to string
 * @info: Parameter struct
 * @str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *po;

	po = _strcharr(str, '=');
	if (!po)
		return (1);
	if (!*++po)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_n_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *po = NULL, *a = NULL;

	if (node)
	{
		po = _strcharr(node->str, '=');
		for (a = node->str; a <= po; a++)
			_putchar(*a);
		_putchar('\'');
		_putsinpt(po + 1);
		_putsinpt("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myaliasb - Mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myaliasb(info_t *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _strcharr(info->argv[i], '=');
		if (ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_s_wchar(info->alias, info->argv[i], '='));
	}

	return (0);
}
