#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
#define PROMPT_STRING "My$hell"

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
 * execute_command - Executes a given command with arguments.
 * @cmd: The command to execute.
 * @args: The array of command arguments.
 *
 * Return: 1 if executed successfully, 0 if not.
 */
int execute_command(char *cmd, char *args[])
{
	if (access(cmd, X_OK) == 0)
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execvp(cmd, args) == -1)
			{
				perror("execvp");
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
		printf("%s: command not found\n", cmd);
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
	char userInput[MAX_INPUT_LENGTH];
	char cmd[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];
	int numArgs;

	while (1)
	{
		printf("%s", PROMPT_STRING);

		if (!fgets(userInput, MAX_INPUT_LENGTH, stdin))
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		remove_newline(userInput);
		numArgs = 0;

		args[numArgs] = strtok(userInput, " ");
		while (args[numArgs] != NULL)
		{
			numArgs++;
			args[numArgs] = strtok(NULL, " ");
		}
		args[numArgs] = NULL;

		if (numArgs > 0)
		{
			execute_command(cmd, args);
		}
	}

	return (EXIT_SUCCESS);
}
