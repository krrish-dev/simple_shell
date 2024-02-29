#include "shell.h"

/**
 * _mycuenv - Prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _mycuenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _gtenv - Gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Env var name
 *
 * Return: The value
 */
char *_gtenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_wchar(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _myunsetenviro - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenviro(info_t *info)
{
	int itr;

	if (info->argc == 1)
	{
		_errputs("Too few arguements.\n");
		return (1);
	}
	for (itr = 1; itr <= info->argc; itr++)
		_rmenv(info, info->argv[itr]);

	return (0);
}

/**
 * p_env_list - Populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int p_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t itr;

	for (itr = 0; environ[itr]; itr++)
		add_n_end(&node, environ[itr], 0);
	info->env = node;
	return (0);
}

/**
 * _myinitilizeenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myinitilizeenv(info_t *info)
{
	if (info->argc != 3)
	{
		_errputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
