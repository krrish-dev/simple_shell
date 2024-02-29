#include "shell.h"

/**
 * find_pstr - Finds this cmd in the PATH string
 * @info: The info struct
 * @pathstr: The PATH string
 * @cmd: The cmd to find
 *
 * Return: Full path of cmd if found or NULL
 */
char *find_pstr(info_t *info, char *pathstr, char *cmd)
{
	int itr = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlength(cmd) > 2) && starts_wchar(cmd, "./"))
	{
		if (is_cpath(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[itr] || pathstr[itr] == ':')
		{
			path = dupli_chars(pathstr, curr_pos, itr);
			if (!*path)
				_strconcat(path, cmd);
			else
			{
				_strconcat(path, "/");
				_strconcat(path, cmd);
			}
			if (is_cpath(info, path))
				return (path);
			if (!pathstr[itr])
				break;
			curr_pos = itr;
		}
		itr++;
	}
	return (NULL);
}

/**
 * is_cpath - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cpath(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupli_chars - Duplicates characters.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to new buffer
 */
char *dupli_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int itr = 0, k = 0;

	for (k = 0, itr = start; itr < stop; itr++)
		if (pathstr[itr] != ':')
			buf[k++] = pathstr[itr];
	buf[k] = 0;
	return (buf);
}
