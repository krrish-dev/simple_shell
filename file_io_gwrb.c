#include "shell.h"


/**
 * wr_history - Creates a file, or appends to an existing file
 * @info: The parameter struct
 *
 * Return: 1 on success, else -1
 */
int wr_history(info_t *info)
{
	ssize_t filed;
	char *filename = g_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filed = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filed == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfiled(node->str, filed);
		_putfiled('\n', filed);
	}
	_putfiled(BUF_FLUSH, filed);
	close(filed);
	return (1);
}

/**
 * bd_history_list - Adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: Buffer
 * @linecount: The history linecount, histcount
 *
 * Return: Always 0
 */
int bd_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_n_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * rembar_history - Renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: The new histcount
 */
int rembar_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

/**
 * g_history_file - Gets the history file
 * @info: Parameter struct
 *
 * Return: Allocated string containg history file
 */

char *g_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _gtenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlength(dir) + _strlength(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcopy(buf, dir);
	_strconcat(buf, "/");
	_strconcat(buf, HIST_FILE);
	return (buf);
}


/**
 * rd_history - Reads history from file
 * @info: The parameter struct
 *
 * Return: Histcount on success, 0 otherwise
 */
int rd_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t filed, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = g_history_file(info);

	if (!filename)
		return (0);

	filed = open(filename, O_RDONLY);
	free(filename);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(filed, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(filed);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			bd_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		bd_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		del_node_at_index(&(info->history), 0);
	rembar_history(info);
	return (info->histcount);
}
