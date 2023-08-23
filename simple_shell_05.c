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
		return (1); /* Command executed successfully */
	}
	else
	{
		printf("%s: command not found\n", cmd);
		return (0); /* Command not found */
	}
}

/**
 * execute_env - Prints the current environment.
 * @envp: The environment variables array.
 */
void execute_env(char **envp)
{
	size_t i;

	for (i = 0; envp[i] != NULL; i++)
	{
		printf("%s\n", envp[i]);
	}
}

/**
 * parse_user_input - Parses user input into arguments.
 * @userInput: The user's input.
 * @args: The array to store parsed arguments.
 */
void parse_user_input(char *userInput, char *args[])
{
	int numArgs = 0;

	args[numArgs] = strtok(userInput, " ");
	while (args[numArgs] != NULL)
	{
		numArgs++;
		args[numArgs] = strtok(NULL, " ");
	}
	args[numArgs] = NULL;
}

/**
 * main - Entry point of the simple shell program.
 * @argc: The number of command line arguments.
 * @argv: The array of command line arguments.
 * @envp: The array of environment variables.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **envp)
{
	char userInput[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];

	/* Avoid unused parameter warnings */
	(void)argc;
	(void)argv;

	while (1)
	{
		printf("%s ", PROMPT_STRING);

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
		parse_user_input(userInput, args);

		if (args[0] != NULL)
		{
			if (strcmp(args[0], "env") == 0)
			{
				execute_env(envp);
			}
			else
			{
				execute_command(args[0], args);
			}
		}
	}

	return (EXIT_SUCCESS);
}
