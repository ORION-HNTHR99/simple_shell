#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

/**
 * remove_newline - Removes the newline character from a string.
 * @str: The string to modify.
 */
void remove_newline(char *str)
{
	char *newline = strchr(str, '\n');

	if (newline)
	{
		*newline = '\0';
	}
}

/**
 * execute_command - Executes a given command.
 * @command: The command to execute.
 *
 * Return: 1 if executed successfully, 0 if not.
 */
int execute_command(char *command)
{
	if (access(command, X_OK) == 0)
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execlp(command, command, NULL) == -1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
		return (1);
	}
	else
	{
		printf("%s: command not found\n", command);
		return (0);
	}
}

/**
 * main - Entry point of the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("#cisfun$ ");

		if (!fgets(input, MAX_INPUT_LENGTH, stdin))
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		remove_newline(input);

		if (!execute_command(input))
		{
			continue;
		}
	}

	return (EXIT_SUCCESS);
}
