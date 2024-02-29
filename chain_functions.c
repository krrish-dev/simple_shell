#include "shell.h"

/**
 * check_chain - Checks we should continue chaining based on last status
 * @info: The parameter struct
 * @buf: The char buffer
 * @p: Address of current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t ji = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			ji = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			ji = len;
		}
	}

	*p = ji;
}

/**
 * rep_vars - Replaces vars in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmpare(info->argv[i], "$?"))
		{
			rep_string(&(info->argv[i]),
				_strrdup(conv_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmpare(info->argv[i], "$$"))
		{
			rep_string(&(info->argv[i]),
				_strrdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = node_s_wchar(info->env, &info->argv[i][1], '=');
		if (node)
		{
			rep_string(&(info->argv[i]),
				_strrdup(_strcharr(node->str, '=') + 1));
			continue;
		}
		rep_string(&info->argv[i], _strrdup(""));

	}
	return (0);
}

/**
 * rep_string - Replaces string
 * @old: Address of old string
 * @new: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}


/**
 * is_chain - Test if current char in buffer is a chain delimeter
 * @info: The parameter struct
 * @buf: The char buffer
 * @p: Address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t ji = *p;

	if (buf[ji] == '|' && buf[ji + 1] == '|')
	{
		buf[ji] = 0;
		ji++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[ji] == '&' && buf[ji + 1] == '&')
	{
		buf[ji] = 0;
		ji++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[ji] == ';') /* got end of this cmd */
	{
		buf[ji] = 0; /* replace ; with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = ji;
	return (1);
}


/**
 * rep_alias - Replaces an aliases in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_s_wchar(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strcharr(node->str, '=');
		if (!p)
			return (0);
		p = _strrdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
