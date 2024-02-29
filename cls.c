#include "shell.h"


/**
 * frees_info - Frees info_t struct fields
 * @info: Struct address
 * @all: True if freeing all fields
 */
void frees_info(info_t *info, int all)
{
	str_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		str_free(info->environ);
			info->environ = NULL;
		freep((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * cls_info - Initializes info_t struct
 * @info: Struct address
 */
void cls_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}


/**
 * setting_info - Initializes info_t struct
 * @info: Struct address
 * @av: Argument vector
 */
void setting_info(info_t *info, char **av)
{
	int itr = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtsw(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strrdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (itr = 0; info->argv && info->argv[itr]; itr++)
			;
		info->argc = itr;

		rep_alias(info);
		rep_vars(info);
	}
}
