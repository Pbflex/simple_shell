#include "shell.h"

/**
* _myenv - this prints the current environment
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
* _getenv - this gets the value of an environ variable
* @info: Structure containing potential arguments. Used to maintain
* @name: env var name
* Return: the value
*/

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *s;

	while (node)
	{
	s = starts_with(node->str, name);
	if (s && *s)
	return (s);
	node = node->next;
	}
	return (NULL);
}

/**
* _mysetenv - this initialize a new environment variable,
*             or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: 0
*/

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
	_eputs("Incorrect number of arguements\n");
	return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	return (0);
	return (1);
}

/**
* _myunsetenv - this removes an environment variable
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: 0
*/
int _myunsetenv(info_t *info)
{
	int e;

	if (info->argc == 1)
	{
	_eputs("Too few arguements.\n");
	return (1);
	}
	for (e = 1; e <= info->argc; e++)
	_unsetenv(info, info->argv[e]);

	return (0);
}

/**
* populate_env_list - this populates env linked list
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: 0
*/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t e;

	for (e = 0; environ[e]; e++)
		add_node_end(&node, environ[e], 0);
	info->env = node;
	return (0);
}
