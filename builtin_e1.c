#include "shell.h"

/**
 * _myexitsh - Exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexitsh(info_t *info)
{
	int excheck;

	if (info->argv[1])  /* If info->argv[1] */
	{
		excheck = _errintostr(info->argv[1]);
		if (excheck == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			_errputs(info->argv[1]);
			_errputchar('\n');
			return (1);
		}
		info->err_num = _errintostr(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mychangecd - Changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mychangecd(info_t *info)
{
	char *str, *dir, buffer[1024];
	int chdir_r;

	str = getcwd(buffer, 1024);
	if (!str)
		_putsinpt("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _gtenv(info, "HOME=");
		if (!dir)
			chdir_r = /* what must be? */
				chdir((dir = _gtenv(info, "PWD=")) ? dir : "/");
		else
			chdir_r = chdir(dir);
	}
	else if (_strcmpare(info->argv[1], "-") == 0)
	{
		if (!_gtenv(info, "OLDPWD="))
		{
			_putsinpt(str);
			_putchar('\n');
			return (1);
		}
		_putsinpt(_gtenv(info, "OLDPWD=")), _putchar('\n');
		chdir_r = /* what must be? */
			chdir((dir = _gtenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_r = chdir(info->argv[1]);
	if (chdir_r == -1)
	{
		print_err(info, "can't cd to ");
		_errputs(info->argv[1]), _errputchar('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", _gtenv(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelppage - Changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelppage(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_putsinpt("help call works. Function not yet implemented \n");
	if (0)
		_putsinpt(*arg_arr); /* Always 0 */
	return (0);
}
