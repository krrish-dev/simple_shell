#include "shell.h"

/**
 * input_buf - Buffers chained commands
 * @info: Parameter struct
 * @buf: Address of buffer
 * @len: Address of len var
 *
 * Return: Bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*freep((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			rm_comments(*buf);
			bd_history_list(info, *buf, info->histcount++);
			/* if (_strcharr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * g_input - Gets a line minus the newline.
 * @info: Parameter struct
 *
 * Return: Bytes read
 */
ssize_t g_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t itr, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = itr; /* init new iterator to current buf position */
		p = buf + itr; /* get pointer for return */

		check_chain(info, buf, &j, itr, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		itr = j + 1; /* increment past nulled ';'' */
		if (itr >= len) /* reached end of buffer? */
		{
			itr = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlength(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}



/**
 * sigHandler - Blocks ctrl-C
 * @sig_num: The signal number
 *
 * Return: Void
 */
void sigHandler(__attribute__((unused))int sig_num)
{
	_putsinpt("\n");
	_putsinpt("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * read_buf - Reads a buffer
 * @info: Parameter struct
 * @buf: Buffer
 * @itr: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *itr)
{
	ssize_t r = 0;

	if (*itr)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*itr = r;
	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t itr, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (itr == len)
		itr = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strcharr(buf + itr, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realcon(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strnccat(new_p, buf + itr, k - itr);
	else
		_strncp(new_p, buf + itr, k - itr + 1);

	s += k - itr;
	itr = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
