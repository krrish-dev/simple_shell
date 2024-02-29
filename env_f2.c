#include "shell.h"

/**
 * _rmenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: The string env var property.
 */
int _rmenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_wchar(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = del_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * get_envstrcp - Returns the string array copy of our env
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_envstrcp(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property
 * @value: The string env var value
 *  Return: Always 0
 */
int _set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buf = malloc(_strlength(var) + _strlength(value) + 2);
	if (!buf)
		return (1);
	_strcopy(buf, var);
	_strconcat(buf, "=");
	_strconcat(buf, value);
	node = info->env;
	while (node)
	{
		ptr = starts_wchar(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_n_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
