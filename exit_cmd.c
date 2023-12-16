#include "shell.h"

/**
 * exit_cmd - handles the exit command
 * @command: tokenized command
 * @line: input read from stdin
 *
 * Return: no return
 */

void exit_cmd(char **command, char *line)
{
	if (command[1] != NULL)
	{
		int status = atoi(command[1]);
		free(line);
		free_buffers(command);
		exit(status);
	}
	else
	{
	free(line);
	free_buffers(command);
	exit(EXIT_SUCCESS);
	}
}
