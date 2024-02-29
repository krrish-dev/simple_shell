#include "shell.h"

/**
 * find_built - Finds a builtin command
 * @info: The parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_built(info_t *info)
{
	int itr, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexitsh},
		{"env", _mycuenv},
		{"help", _myhelppage},
		{"history", _mydphistory},
		{"setenv", _myinitilizeenv},
		{"unsetenv", _myunsetenviro},
		{"cd", _mychangecd},
		{"alias", _myaliasb},
		{NULL, NULL}
	};

	for (itr = 0; builtintbl[itr].type; itr++)
		if (_strcmpare(info->argv[0], builtintbl[itr].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[itr].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * fork_c - Forks a an exec thread to run cmd
 * @info: The parameter & return info struct
 *
 * Return: Void
 */
void fork_c(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_envstrcp(info)) == -1)
		{
			frees_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}


/**
 * hsh_char - Main shell loop
 * @info: The parameter & return info struct
 * @av: The argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh_char(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		cls_info(info);
		if (interact(info))
			_putsinpt("$ ");
		_errputchar(BUF_FLUSH);
		r = g_input(info);
		if (r != -1)
		{
			setting_info(info, av);
			builtin_ret = find_built(info);
			if (builtin_ret == -1)
				find_c(info);
		}
		else if (interact(info))
			_putchar('\n');
		frees_info(info, 0);
	}
	wr_history(info);
	frees_info(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}


/**
 * find_c - Finds a command in PATH
 * @info: The parameter & return info struct
 *
 * Return: Void
 */
void find_c(info_t *info)
{
	char *path = NULL;
	int itr, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (itr = 0, k = 0; info->arg[itr]; itr++)
		if (!is_delimstr(info->arg[itr], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_pstr(info, _gtenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_c(info);
	}
	else
	{
		if ((interact(info) || _gtenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cpath(info, info->argv[0]))
			fork_c(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}
