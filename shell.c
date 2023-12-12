#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

void display_prompt()
{
	char prompt[] = "$ ";
	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
	fflush(stdout);
}

int execute_command (char *command)
{
	pid_t pid = fork();

	if (pid ==0)
	{
		/*Child process*/
		char *args[] = {command, NULL};
		execve(command, args, NULL);
		perror("./shell:");
		_exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		/*parent*/
		int status;
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			return WEXITSTATUS(status);
		}
		else
		{
			return -1; // Failed to execute the command
		}
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

int main()
{
	char *command = NULL;
	size_t command_size = 0;

	while (1)
	{
		display_prompt();

		ssize_t read_size = getline(&command, &command_size, stdin);

		if (read_size == -1)
		{
			/*handle Ctrl+D (End of file)*/
			char exit_message[] = "\nExiting the shell.\n";
			write(STDOUT_FILENO, exit_message, sizeof(exit_message) - 1);
			break;
		}
		/*remove newline*/
		command[strcspn(command, "\n")] = '\0';

		if (strlen(command) == 0)
		{
			continue;
		}
		if (strcmp(command, "exit") == 0)
		{
			char exit_message[] = "Exiting the shell.\n";
			write(STDOUT_FILENO, exit_message, sizeof(exit_message) - 1);
			break;
		}
		int exit_code = execute_command(command);

		if (exit_code == -1)
		{
			char error_message[] = "Failed to execute the command.\n";
			write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
		}
		else
		{
			char exit_status_message[MAX_COMMAND_LENGTH];
			int len = snprintf(exit_status_message, sizeof(exit_status_message), "Exit status: %d\n", exit_code);
			write(STDOUT_FILENO, exit_status_message, len);
		}
	}
	free (command);

	return EXIT_SUCCESS;
}
