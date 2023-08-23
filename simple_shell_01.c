#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

/**
 * remove_newline - Removes the newline character from a string.
 * @str: The string to modify.
 */
void remove_newline(char *str)
{
	/* Find the newline character */
	char *newline = strchr(str, '\n');

	/* If found, replace it with null terminator */
	if (newline)
	{
		*newline = '\0';
	}
}

/**
 * execute_command - Executes a given command.
 * @cmd: The command to execute.
 *
 * Return: 1 if executed successfully, 0 if not.
 */
int execute_command(char *cmd)
{
	/* Check if the command is executable */
	if (access(cmd, X_OK) == 0)
	{
		pid_t child_pid = fork();

		/* Check for fork error */
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		/* Child process */
		else if (child_pid == 0)
		{
			/* Execute the command */
			if (execlp(cmd, cmd, (char *)NULL) == -1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
		}
		/* Parent process */
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
	char user_input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("#myshell$ ");

		/* Get user input */
		if (!fgets(user_input, MAX_INPUT_LENGTH, stdin))
		{
			/* Check for end of file */
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		/* Remove newline character */
		remove_newline(user_input);

		/* Check for exit command */
		if (strcmp(user_input, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}

		/* Execute the command */
		if (strlen(user_input) > 0)
		{
			if (!execute_command(user_input))
			{
				continue;
			}
		}
	}

	return (EXIT_SUCCESS);
}
